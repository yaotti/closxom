#include "hello.h"
#include "closxom.h"

using namespace std;
using namespace closxom;

int main(int argc, char **argv)
{
    const Config config("/Users/hiroshige/active/intern-prep/p/closxom/test-files/");

    Closxom *closxom = new Closxom(config, string("html"));
    cout << "content-type: text/html" << endl << endl;
    closxom->Dispatch();
    return 0;
}


