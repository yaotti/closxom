#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "closxom_storage_protobuf.h"


namespace closxom {
void StorageProtobuf::Init() {
    EntryStorage *storage = new EntryStorage();
    {
        std::fstream input(this->filename().c_str(), std::ios::in | std::ios::binary);
        if (!(*storage).ParseFromIstream(&input)) {
            std::cerr << "Failed to parse entry storage." << std::endl;
            exit(1);
        }
    }
    storage_ = storage;
}

int StorageProtobuf::EntrySize() {
    return this->storage()->entry_size();
}

void StorageProtobuf::ExtractEntry(int idx, Entry* entry) {
    *entry = this->storage()->entry(idx);
}

} // namespace clsxom
