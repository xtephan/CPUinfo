#ifndef SYSINFO_H
#define SYSINFO_H


class sysinfo
{
    public:
        sysinfo();
        virtual ~sysinfo();
        void hello();
        void display_info();
        void menu();
    protected:
    private:

        void harvest_data();     // Get basic system data
        char username[64];       // username that runs the program
        char *get_kernel_version(); //return the kernel version
        char linux_version[64]; // kernel version
        char linux_distro[64];
        char *get_linux_distro();
        char *get_date();
        void cpu_detailes(); //displays detailed informations about the CPU
        void ps_show(); //displays running procceses
        void ps_show( char name[] ); //displays running procceses
        void kill_ps( char id[] ); //displays running procceses
        void cpu_usg(); //displays running procceses
        void mem_usg(); //displays running procceses
};

#endif
