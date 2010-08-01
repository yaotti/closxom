#include <sys/dir.h>
#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "closxom_storage_filesystem.h"


namespace closxom {
void StorageFileSystem::Init() {
    entry_file_paths_ = this->GetEntryPaths(this->rootpath());
}

int StorageFileSystem::EntrySize() {
    return this->entry_file_paths().size();
}

void StorageFileSystem::ExtractEntry(int idx, Entry* entry) {
    std::string path = this->entry_file_paths()[idx];
    std::ifstream ifs(path.c_str());
    if (ifs == NULL) {
        std::cerr << "Cannot Open File: " << path << std::endl;
        exit(1);
    }

    std::string line("");
    std::getline(ifs, line);
    entry->set_title(line);
    std::stringstream sstr;
    sstr << ifs.rdbuf();
    entry->set_body(sstr.str());
    /* datetime */
    struct stat attrib;
    stat(path.c_str(), &attrib);
    const struct tm *clock = gmtime(&(attrib.st_mtime));
    char datetime[15];           /* YYYYMMDDHHMMSS */
    sprintf(datetime, "%04d%02d%02d%02d%02d%02d", clock->tm_year+1900, clock->tm_mon+1, clock->tm_mday, clock->tm_hour, clock->tm_min, clock->tm_sec);
    //delete clock;
    entry->set_modified_datetime(datetime);
}

std::vector<std::string> StorageFileSystem::GetEntryPaths(const std::string path) {
    DIR* dir;
    struct dirent* dp;
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
    delete dp;
    return entry_paths;
}

} // namespace clsxom
