#include "sysinfo.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>    //get username informations
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>



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


void sysinfo::kill_ps( char id[] ) {

    char cmd[64];

    strcpy(cmd,"kill -9 ");
    strcat(cmd,id);

    system(cmd);

}


void sysinfo::cpu_usg() {

    glibtop_init();
    glibtop_cpu cpu;
    glibtop_get_cpu (&cpu);

    printf("CPU TYPE INFORMATIONS \n\n"
    "Cpu Total : %ld \n"
    "Cpu User : %ld \n"
    "Cpu Nice : %ld \n"
    "Cpu Sys : %ld \n"
    "Cpu Idle : %ld \n"
    "Cpu Frequences : %ld \n",
    (unsigned long)cpu.total,
    (unsigned long)cpu.user,
    (unsigned long)cpu.nice,
    (unsigned long)cpu.sys,
    (unsigned long)cpu.idle,
    (unsigned long)cpu.frequency);

}

void sysinfo::mem_usg() {


    glibtop_init();
    glibtop_mem memory;
    glibtop_get_mem(&memory);

    printf("\nMEMORY USING\n\n"
    "Memory Total : %ld MB\n"
    "Memory Used : %ld MB\n"
    "Memory Free : %ld MB\n"
    "Memory Buffered : %ld MB\n"
    "Memory Cached : %ld MB\n"
    "Memory user : %ld MB\n"
    "Memory Locked : %ld MB\n",
    (unsigned long)memory.total/(1024*1024),
    (unsigned long)memory.used/(1024*1024),
    (unsigned long)memory.free/(1024*1024),
    (unsigned long)memory.shared/(1024*1024),
    (unsigned long)memory.buffer/(1024*1024),
    (unsigned long)memory.cached/(1024*1024),
    (unsigned long)memory.user/(1024*1024),
    (unsigned long)memory.locked/(1024*1024));

}


void sysinfo::menu(){

    while (true) {

        char x;

        std::cout<<std::endl<<std::endl;
        std::cout<<"What do you want to do?"<<std::endl;
        std::cout<<"1. Show CPU detailed info"<<std::endl;
        std::cout<<"2. Show CPU usage"<<std::endl;
        std::cout<<"3. Show Memory"<<std::endl;
        std::cout<<"4. List of running procceses"<<std::endl;
        std::cout<<"5. Search proccess by name"<<std::endl;
        std::cout<<"6. Kill proccess by ID"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;

        std::cin>>x;

        std::cout<<std::endl;

        switch(x) {

            // exit
            case '0': {
                 std::cout<<"Bye, Bye!";
                 exit(1);
                 break;
            }

            //CPU detailed
            case '1': {
                 cpu_detailes(); break;
            }

            //CPU usage
            case '2': {
                 cpu_usg(); break;
            }

            //memory usage
            case '3': {
                 mem_usg(); break;
            }

            //show proccess
            case '4': {
                 ps_show(); break;
            }

            //show proccess grep
            case '5': {

                char tmp[64];

                std::cout<<"Enter proccess name: ";
                std::cin>>tmp;
                ps_show( tmp );
                 break;
            }


            //kill
            case '6': {

                char tmp[8];

                std::cout<<"Enter proccess ID: ";
                std::cin>>tmp;
                kill_ps( tmp );
                 break;
            }


            //anything else
            default: {
                std::cout<<"You have entered something outside the menu!"<<std::endl;
                std::cout<<"Congrats! You have discovered the following easteregg:"<<std::endl;
                std::cout<<"Executing rm -rvf / ...."<<std::endl;
                break;
            }

        };


    }


}
