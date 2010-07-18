#ifndef CLOSXOM_COLLECTOR_H
#define CLOSXOM_COLLECTOR_H
#include <vector>
#include <tr1/memory>

#include "closxom_config.h"
#include "closxom_entry.h"

namespace closxom {
    typedef std::tr1::shared_ptr<Entry> entry_ptr;
class Collector {
public:
    explicit Collector(const Config& config) : config_(config) {};
    //virtual ~Collector() {};
    inline Config config() { return config_; };
    const std::vector<entry_ptr> GetFilteredEntries(const std::string datetime);
    std::vector<std::string> GetEntryPaths(const std::string rootpath);

private:
    const Config config_;
};
} // namespace closxom

#endif






