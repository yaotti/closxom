#ifndef CLOSXOM_CONFIG_H
#define CLOSXOM_CONFIG_H
#include <string>

namespace closxom {
class Config {
public:
    Config(const std::string rootpath) : rootpath_(rootpath) {};
    virtual ~Config() {};
    inline std::string rootpath() { return rootpath_; };

private:
    const std::string rootpath_;
};
} // namespace closxom

#endif
