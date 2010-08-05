#ifndef CLOSXOM_STORAGE_H
#define CLOSXOM_STORAGE_H

#include "closxom.pb.h"

namespace closxom {
class Storage {
public:
    Storage() {};
    Storage(const std::string key) {};
    //virtual ~Storage();
    virtual void Init() = 0;
    virtual int EntrySize() = 0;
    virtual void ExtractEntry(int idx, Entry* entry) = 0;
private:
};
} // namespace closxom
#endif
