#ifndef CLOSXOM_COLLECTOR_H
#define CLOSXOM_COLLECTOR_H
#include <vector>
#include <tr1/memory>

#include "closxom_config.h"
#include "closxom_entry.h"

#include "closxom.pb.h"
#include "closxom_storage.h"
#include "closxom_storage_filesystem.h"

namespace closxom {
typedef std::tr1::shared_ptr<const Entry> entry_ptr;
class Collector {
public:
    explicit Collector(const Config& config) : config_(config) {};
    void Init();
    virtual ~Collector() {};
    inline Config config() { return config_; };
    template <class T> void set_storage(T* storage) { storage_ = storage; };
    Storage* storage() { return storage_; };
    const std::vector<entry_ptr> GetFilteredEntries(const std::string datetime);
    std::vector<std::string> GetEntryPaths(const std::string rootpath);

private:
    const Config config_;
    Storage* storage_;
};
} // namespace closxom

#endif
