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

void Collector::Init() {
    if (this->config().storage_type() == "protobuf") {
        //this->set_storage(new StorageProtoBuf(""));
    }else // if (this->config().storage_type() == "filesystem")
        {
        StorageFileSystem* storage = new StorageFileSystem("/Users/hiroshige/active/intern-prep/p/closxom/test-files/");
        storage->Init();
        std::cout << "collector::init------------------------------" << std::endl;
        std::cout << storage->debug() << std::endl; // XXX
        this->set_storage(storage);
    }
}

const std::vector<entry_ptr> Collector::GetFilteredEntries(const std::string datetime) {
    //std::vector<entry_ptr> entries;
//     if (this->config().storage_type() == "protobuf") {       // use protobuf
//         EntryStorage storage;
//         std::fstream input("entries.pb", std::ios::in | std::ios::binary); // XXX
//         if (!storage.ParseFromIstream(&input)) { // XXX: don't use stream!!!!
//             std::cerr << "Failed to parse entries." << std::endl;
//             exit(1);
//         }
//         for (int i = 0; i < storage.entry_size(); i++) {
//             const Entry* entry = &storage.entry(i);
//             // filtering by datetime
//             if (datetime != "" && entry->modified_datetime().compare(0, datetime.length(), datetime) != 0) continue;
//             entry_ptr entry_p = entry_ptr(entry);
//             entries.push_back(entry_p);
//         }
//     }else {
//         std::vector<std::string> entry_paths = this->GetEntryPaths("");
        std::vector<entry_ptr> entries;
        for (int i = 0; i < this->storage()->EntrySize(); i++) {
            // XXX: スコープを抜けるとentryが消える
            // 引数で場所を確保しておく?
            const Entry* entry = this->storage()->ExtractEntry(i);
            // filtering by datetime
            if (datetime != "" && entry->modified_datetime().compare(0, datetime.length(), datetime) != 0) continue;
            entry_ptr entry_p = entry_ptr(entry);
            entries.push_back(entry_p);
        }
        std::cout << "loop out" << std::endl;
//     }
    sort(entries.begin(), entries.end(), EntryDateSorter()); // sort by mtime
    return entries;
}

}
