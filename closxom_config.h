#ifndef CLOSXOM_CONFIG_H
#define CLOSXOM_CONFIG_H
#include <string>

namespace closxom {
class Config {
public:
    Config(const std::string storage_type) : storage_type_(storage_type) {};
    virtual ~Config() {};
    void set_rootpath(std::string rootpath) { rootpath_ = rootpath; }; // XXX: check storage type
    inline std::string storage_type() { return storage_type_; };
    inline std::string rootpath() { return rootpath_; };

private:
    const std::string storage_type_;
    std::string rootpath_;
};
} // namespace closxom

#endif
