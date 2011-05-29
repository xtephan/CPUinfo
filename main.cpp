#include <iostream>
#include "sysinfo.h"

using namespace std;

int main()
{
    sysinfo SI;

    //dummy function, used for testing porpuses only
    SI.hello();

    //Display a greeting and info
    SI.display_info();


    return 0;
}
