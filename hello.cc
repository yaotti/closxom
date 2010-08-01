#include "closxom.h"

using namespace std;
using namespace closxom;

//static string rootpath("/PATH/TO/DATA/DIR/");
static string rootpath("/Users/hiroshige/active/intern-prep/p/closxom/");

int main(int argc, char **argv)
{
    string storage_type = "filesystem";
    //string storage_type = "protobuf";

    Config config(storage_type);
    config.set_rootpath(rootpath);

    Closxom closxom(config);
    closxom.Dispatch();
    return 0;
}
