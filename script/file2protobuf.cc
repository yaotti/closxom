// serialize file contents into protobuf file
// g++ -I. -o script/file2protobuf.o -O2 closxom.pb.cc script/file2protobuf.cc `pkg-config --cflags --libs protobuf`
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "closxom.pb.h"

using namespace std;
using namespace closxom;

void SetEntryFromFile(char* filename, Entry* entry) {
    std::ifstream ifs(filename);
    if (ifs == NULL) {
        std::cerr << "Cannot Open File: " << filename << std::endl;
        exit(1);
    }

    std::string line("");
    std::getline(ifs, line);
    entry->set_title(line);
    std::stringstream sstr;
    sstr << ifs.rdbuf();
    entry->set_body(sstr.str());
    /* datetime */
    struct stat attrib;
    stat(filename, &attrib);
    const struct tm *clock = gmtime(&(attrib.st_mtime));
    char datetime[15];           /* YYYYMMDDHHMMSS */
    sprintf(datetime, "%04d%02d%02d%02d%02d%02d", clock->tm_year+1900, clock->tm_mon+1, clock->tm_mday, clock->tm_hour, clock->tm_min, clock->tm_sec);
    entry->set_modified_datetime(datetime);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " INPUT_FILE OUTPUT_FILE" << endl;
        return -1;
    }

    EntryStorage storage;
    {
        fstream input(argv[2], ios::in | ios::binary);
        if (!input) {
            cout << argv[2] << ": File not found.  Creating a new file." << endl;
        } else if (!storage.ParseFromIstream(&input)) {
            cerr << "Failed to parse entry storage." << endl;
            return -1;
        }
    }

    SetEntryFromFile(argv[1], storage.add_entry());

    {
        fstream output(argv[2], ios::out | ios::trunc | ios::binary);
        if (!storage.SerializeToOstream(&output)) {
            cerr << "Failed to write entry storage." << endl;
            return -1;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
