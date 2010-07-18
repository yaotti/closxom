#include "hello.h"
#include "closxom.h"

using namespace std;
using namespace closxom;

int main(int argc, char **argv)
{
    const Config config("/Users/hiroshige/active/intern-prep/p/closxom/test-files/");

    Closxom *closxom = new Closxom(config, string("html"));
    Collector *collector = new Collector(config);
    const string datetime("2010");

    closxom->set_entries(collector->GetFilteredEntries(datetime));


    cout << "content-type: text/html" << endl << endl;
    cout << closxom->RenderEntries();

    return 0;
}


