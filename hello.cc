#include "closxom.h"

using namespace std;
using namespace closxom;

static string datarootpath("/PATH/TO/DATA/DIR/");

int main(int argc, char **argv)
{
    string storage_type = "filesystem";
    Config config(storage_type);
    config.set_rootpath(datarootpath);

    Closxom closxom(config);
    closxom.Dispatch();
    return 0;
}
