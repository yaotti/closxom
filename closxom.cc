#include "closxom.h"

namespace closxom {
void Closxom::CollectEntries(const std::string datetime) {
    Collector* collector = new Collector(this->config());
    const std::vector<entry_ptr> entries = collector->GetFilteredEntries(datetime);
    this->set_entries(entries);
}

const std::string Closxom::RenderEntries() {
    std::string rootpath = this->config().rootpath();
    std::ifstream entry_ifs((rootpath+std::string("../templates/entry.html")).c_str());
    std::stringstream entry_sstream;
    entry_sstream << entry_ifs.rdbuf();
    const char* entry_format = entry_sstream.str().c_str();

    std::string entries_content("");
    for (int i = 0; i < (int)this->entries().size(); i++) {
        Entry entry = *(this->entries()[i]);
        char buf[2048];         // XXX
        sprintf(buf, entry_format, entry.title().c_str(), entry.body().c_str(), entry.modified_datetime().c_str());
        entries_content.append(std::string(buf));
    }

    std::ifstream whole_ifs((rootpath+std::string("../templates/template.html")).c_str());
    std::stringstream whole_sstream;
    whole_sstream << whole_ifs.rdbuf();
    const char* whole_format = whole_sstream.str().c_str();

    char buf[8192];         // XXX
    sprintf(buf, whole_format, entries_content.c_str());
    const std::string content(buf);
    return content;
}

} // namespace closxom
