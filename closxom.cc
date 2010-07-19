#include "closxom.h"

namespace closxom {
void Closxom::CollectEntries(const std::string datetime) {
    Collector* collector = new Collector(this->config());
    const std::vector<entry_ptr> entries = collector->GetFilteredEntries(datetime);
    this->set_entries(entries);
}

const std::string Closxom::RenderEntries() {
    std::string rootpath = this->config().rootpath();
    std::ifstream entry_ifs((rootpath+std::string("../templates/entry.")+this->flavour()).c_str());
    std::stringstream entry_sstream;
    entry_sstream << entry_ifs.rdbuf();
    std::string entries_content("");
    std::string entry_format_string = entry_sstream.str();
    for (int i = 0; i < (int)this->entries().size(); i++) {
        const char* const entry_format = entry_format_string.c_str(); // ループ外に出すとconstなのに書き換えられてしまう
        Entry entry = *(this->entries()[i]);
        char buf[2048];         // XXX
        sprintf(buf, entry_format, entry.title().c_str(), entry.body().c_str(), entry.modified_datetime().c_str());
        entries_content.append(std::string(buf));
    }

    std::ifstream whole_ifs((rootpath+std::string("../templates/template.")+this->flavour()).c_str());
    std::stringstream whole_sstream;
    whole_sstream << whole_ifs.rdbuf();
    const char* whole_format = whole_sstream.str().c_str();

    char buf[8192];         // XXX
    sprintf(buf, whole_format, entries_content.c_str());
    std::string header("content-type:text/"); // content-type
    header.append(this->flavour());
    header.append("\n\n");
    const std::string content(header+std::string(buf));
    return content;
}

void Closxom::Dispatch() {
    std::string path_info(getenv("PATH_INFO"));
    std::string datetime("");
    if (path_info != "/index") {
        for (int i = 1; i < path_info.length(); i++) {
            if (path_info[i] == '/') continue;
            if (path_info[i] == '.') { // flavour
                this->set_flavour(path_info.substr(i+1, path_info.length()-1));
                break;
            }
            datetime.push_back(path_info[i]);
        }
    }
    if (this->flavour() == "") {
        this->set_flavour(std::string("html"));
    }
    Collector* collector = new Collector(this->config());
    this->CollectEntries(datetime);
    puts(this->RenderEntries().c_str());
}

} // namespace closxom
