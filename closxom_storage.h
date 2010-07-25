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
    //inline Config config() { return config_; };
    virtual const Entry* ExtractEntry(int idx) = 0;
    // test
    int debug() { return 1; };
private:
    //Config config_;
};
} // namespace closxom
#endif
