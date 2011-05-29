#include "sysinfo.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>    //get username informations
#include <time.h>
#include <stdio.h>


sysinfo::sysinfo()
{
    //ctor
}

sysinfo::~sysinfo()
{
    //dtor
}

void sysinfo::hello() {

    std::cout<<"Good morning, mortals!"<<std::endl;

}


//return date and time
char *sysinfo::get_date() {

    time_t  rawtime;
    time ( &rawtime );


    char    dt[100];
    strcpy(dt,"");

    strcpy( &dt[0], ctime(&rawtime) );
    return &dt[0];
}


//get kernel version from /proc
char *sysinfo::get_kernel_version() {

    std::ifstream file_op("/proc/version");
    char kv[128];
    strcpy(kv,"");

    //Get kernel name and version
    for(int i=0; i<3; i++) {
        char tmp[32];
        file_op>>tmp;
        strcat(kv,tmp);
        strcat(kv," ");
    }

    file_op.close();

    //Work-around for returning the string
    //In C++ it's harder to shoot yourself in the foot,
    //...but when you do, you blow off your whole leg.
    char aux[128];
    strcpy(&aux[0],kv);

    return &aux[0];

}


char *sysinfo::get_linux_distro() {

    char buff[32];

    FILE *fp = popen("lsb_release -d", "r" );
    fgets( buff, sizeof buff, fp );
    pclose( fp );


    buff[strlen(buff)-1]=NULL;

    char aux[128];
    strcpy(&aux[0],buff+13);

    return &aux[0];
}



void sysinfo::harvest_data() {

    //get the username
    strcpy(username,getlogin());

    //get the kernel version
    strcpy(linux_version,get_kernel_version());

    //get the distro
    strcpy(linux_distro,get_linux_distro());


    std::cout<<"Harnesting data.."<<std::endl<<std::endl;

}


void sysinfo::display_info() {


    harvest_data();

    std::cout<<"Good morning, "<<username<<"!"<<std::endl;
    std::cout<<"How are you on this fine day of "<<get_date()<<"?"<<std::endl;
    std::cout<<"FYI you are running "<<linux_distro<<" with the kernel "<<linux_version<<"!"<<std::endl;


}
