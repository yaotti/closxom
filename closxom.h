#ifndef CLOSXOM_H
#define CLOSXOM_H

#include "closxom_collector.h"

namespace closxom {
class Closxom {
public:
    Closxom(const Config& config, std::string flavour) : config_(config), flavour_(flavour) {};
    inline std::vector<entry_ptr> entries() { return entries_; };
    inline void set_entries(std::vector<entry_ptr> entries) { entries_ = entries; };
    inline Config config() { return config_; };
    inline std::string flavour() { return flavour_; };
    //virtual ~Closxom();
    void CollectEntries(const std::string datetime);
    const std::string RenderEntries();
private:
    const Config config_;
    const std::string flavour_;
    std::vector<entry_ptr> entries_;
};
} // namespace closxom

#endif
