#ifndef SYSINFO_H
#define SYSINFO_H


class sysinfo
{
    public:
        sysinfo();
        virtual ~sysinfo();
        void hello();
        void display_info();
    protected:
    private:
        // Get basic system data
        void harvest_data();
        char username[64];       // username that runs the program
        char *get_kernel_version(); //return the kernel version
        char linux_version[64]; // kernel version
        char linux_distro[64];
        char *get_linux_distro();
        char *get_date();
};

#endif
