#include "sysinfo.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>    //get username informations
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


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


void sysinfo::cpu_detailes() {

    std::ifstream file_op("/proc/cpuinfo");

    char prev[128];

    while(!file_op.eof()) {

        char tmp[128];

        //file_op.getline(tmp,128);
        file_op>>tmp;
        std::cout<<tmp<<" ";

        if ( strcmp(prev,":") == 0 )
            std::cout<<std::endl;


        strcpy(prev,tmp);
    }

    file_op.close();
}


void sysinfo::ps_show() {

    FILE *fp = popen("ps aux", "r" );

    char buff[128];

    while ( fgets( buff, sizeof buff, fp ) )
        std::cout<<buff;

    pclose( fp );

}


void sysinfo::ps_show( char name[] ) {

    char cmd[64];

    strcpy(cmd,"ps aux | grep -i ");
    strcat(cmd,name);


    FILE *fp = popen(cmd, "r" );

    char buff[128];

    while ( fgets( buff, sizeof buff, fp ) )
        std::cout<<buff;

    pclose( fp );

}

void sysinfo::menu(){

    while (true) {

        char x;

        std::cout<<std::endl<<std::endl;
        std::cout<<"What do you want to do?"<<std::endl;
        std::cout<<"1. Show CPU detailed info"<<std::endl;
        std::cout<<"xxx 2. Show CPU usage xxx removed due to compilation/portage issues"<<std::endl;
        std::cout<<"3. List of running procceses"<<std::endl;
        std::cout<<"4. Search proccess by name"<<std::endl;
        std::cout<<"5. Kill proccess by ID"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;

        std::cin>>x;

        std::cout<<std::endl;

        switch(x) {

            case '0': {
                 std::cout<<"Bye, Bye!";
                 exit(1);
                 break;
            }

            case '1': {
                 cpu_detailes(); break;
            }

            case '3': {
                 ps_show(); break;
            }

            case '4': {

                char tmp[64];

                std::cout<<"Enter proccess name: ";
                std::cin>>tmp;
                ps_show( tmp );
                 break;
            }

            default: {
                std::cout<<"You have entered something outside the menu!"<<std::endl;
                std::cout<<"Congrats! You have discovered the following easteregg:"<<std::endl;
                std::cout<<"Executing rm -rvf / ...."<<std::endl;
                break;
            }

        };


    }


}
