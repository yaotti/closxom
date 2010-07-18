#ifndef CLOSXOM_ENTRY_H
#define CLOSXOM_ENTRY_H
#include <time.h>
#include <sys/dir.h>
#include <sys/stat.h>

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "closxom_config.h"


namespace closxom {
class Entry {
public:
    explicit Entry(const std::string path) {
        std::ifstream ifs(path.c_str());
        if (ifs == NULL) {
            std::cerr << "Cannot Open File: " << path << std::endl;
            exit(1);
        }
        std::string line("");
        std::getline(ifs, line);
        title_ = line;
        std::stringstream sstr;
        sstr << ifs.rdbuf();
        body_ = sstr.str();
        /* datetime */
        struct stat attrib;
        stat(path.c_str(), &attrib);
        const struct tm *clock = gmtime(&(attrib.st_mtime));
        char datetime[15];           /* YYYYMMDDHHMMSS */
        sprintf(datetime, "%04d%02d%02d%02d%02d%02d", clock->tm_year+1900, clock->tm_mon+1, clock->tm_mday, clock->tm_hour, clock->tm_min, clock->tm_sec);
        modified_datetime_ = std::string(datetime);
    };
    Entry(const std::string title, const std::string body, const std::string modified_datetime)
        : title_(title), body_(body), modified_datetime_(modified_datetime) {};
    //virtual ~Entry() {};
    inline const std::string title() { return title_; };
    inline const std::string body() { return body_; };
    inline const std::string modified_datetime() { return modified_datetime_; };

private:
    std::string title_;
    std::string body_;
    std::string modified_datetime_;

};
} // namespace closxom

#endif
