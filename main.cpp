#include <iostream>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>
#include "sysinfo.h"

using namespace std;

int main()
{
    sysinfo SI;

    //dummy function, used for testing porpuses only
    SI.hello();

    //Display a greeting and info
    SI.display_info();


    SI.menu();


    return 0;
}
