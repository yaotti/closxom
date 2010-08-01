#ifndef CLOSXOM_STORAGE_FILESYSTEM_H
#define CLOSXOM_STORAGE_FILESYSTEM_H

#include "closxom_storage.h"

namespace closxom {
class StorageFileSystem : public Storage {
public:
    StorageFileSystem(const std::string rootpath) : rootpath_(rootpath) {};
    //virtual ~StorageFileSystem();
    void Init();
    int EntrySize();
    void ExtractEntry(int idx, Entry* entry);
    inline const std::string rootpath() { return rootpath_; };
    inline const std::vector<std::string> entry_file_paths() { return entry_file_paths_; };
private:
    std::vector<std::string> GetEntryPaths(const std::string path);
    const std::string rootpath_;
    std::vector<std::string> entry_file_paths_;
};
} // namespace closxom

#endif
