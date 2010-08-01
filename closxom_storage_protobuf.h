#ifndef CLOSXOM_STORAGE_PROTOBUF_H
#define CLOSXOM_STORAGE_PROTOBUF_H

#include "closxom_storage.h"
#include "closxom.pb.h"

namespace closxom {
class StorageProtobuf : public Storage {
public:
    StorageProtobuf(const std::string filename) : filename_(filename) {};
    //virtual ~StorageProtobuf();
    void Init();
    int EntrySize();
    void ExtractEntry(int idx, Entry* entry);
    inline const std::string filename() { return filename_; };
    inline const EntryStorage* storage() { return storage_; };
private:
    const std::string filename_;
    const EntryStorage* storage_;
};
} // namespace closxom

#endif

