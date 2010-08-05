#include <sys/dir.h>
#include <functional>

#include "closxom_collector.h"

class Storage;
namespace closxom {
class EntryDateSorter : public std::binary_function<entry_ptr, entry_ptr, bool> {
public:
    bool operator()(const entry_ptr& a, const entry_ptr& b) {
        return (a->modified_datetime() < b->modified_datetime());
    }
};

void Collector::Init() {
    Storage* storage;
    if (this->config().storage_type() == "protobuf") {
        storage = new StorageProtobuf(this->config().rootpath()+std::string("entries.pb")); // XXX
    }else if (this->config().storage_type() == "filesystem") {
        storage = new StorageFileSystem(this->config().rootpath()+std::string("test-files/")); // XXX
    }
    storage->Init();
    this->set_storage(storage);
}

const std::vector<entry_ptr> Collector::GetFilteredEntries(const std::string datetime) {
    std::vector<entry_ptr> entries;
    for (int i = 0; i < this->storage()->EntrySize(); i++) {
        Entry* entry = new Entry();
        this->storage()->ExtractEntry(i, entry);
        // filtering by datetime
        if (datetime != "" && entry->modified_datetime().compare(0, datetime.length(), datetime) != 0) continue;
        entry_ptr entry_p = entry_ptr(entry);
        entries.push_back(entry_p);
    }
    sort(entries.begin(), entries.end(), EntryDateSorter()); // sort by mtime
    return entries;
}

}
