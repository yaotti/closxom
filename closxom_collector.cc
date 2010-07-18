#include <sys/dir.h>
#include <functional>

#include "closxom_collector.h"

namespace closxom {
class EntryDateSorter : public std::binary_function<entry_ptr, entry_ptr, bool> {
public:
    bool operator()(const entry_ptr& a, const entry_ptr& b) {
        return (a->modified_datetime() < b->modified_datetime());
    }
};

const std::vector<entry_ptr> Collector::GetFilteredEntries(const std::string datetime) {
    std::vector<std::string> entry_paths = this->GetEntryPaths("");
    std::vector<entry_ptr> entries;
    for (int i = 0; i < (int)entry_paths.size(); i++) {
        Entry *entry = new Entry(entry_paths[i]);
        // filtering by datetime
        if (datetime != "" && entry->modified_datetime().compare(0, datetime.length(), datetime) != 0) continue;
        entries.push_back(entry_ptr(entry));
    }
    sort(entries.begin(), entries.end(), EntryDateSorter()); // sort by mtime
    return entries;
}

std::vector<std::string> Collector::GetEntryPaths(const std::string rootpath) {
    DIR* dir;
    struct dirent* dp;
    std::string path = rootpath;
    if (path == "") {
        path = this->config().rootpath();
    }
    if ((dir = opendir(path.c_str())) == NULL) {
        std::cerr << "Can't open directory: " << path << std::endl;
        exit(1);
    }
    std::vector<std::string> entry_paths;
    while ((dp = readdir(dir)) != NULL) {
        if (dp->d_name[0] == '.') continue;         // pass "." and ".."
        std::string file_path(path);
        file_path.append(std::string(dp->d_name));
        if (dp->d_type == DT_DIR) {                 // directory
            file_path.append("/");
            std::vector<std::string> subdir_entry_paths =
                this->GetEntryPaths(file_path);
            // merge result to return value
            for (std::vector<std::string>::iterator it = subdir_entry_paths.begin(); it != subdir_entry_paths.end(); it++) {
                entry_paths.push_back(*it);
            }
        }else {                 // file
            entry_paths.push_back(file_path);
        }
    }
    return entry_paths;
}
}
