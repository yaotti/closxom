#include "closxom.h"

using namespace std;
using namespace closxom;

static string datarootpath("/PATH/TO/DATA/DIR/");

int main(int argc, char **argv)
{
    const Config config(datarootpath);
    Closxom *closxom = new Closxom(config);
    closxom->Dispatch();
    return 0;
}
