#include <stdio.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <glibtop/proclist.h>
int main()
{
glibtop_init();
glibtop_cpu cpu;
glibtop_mem memory;
glibtop_proclist proclist;
glibtop_get_cpu (&cpu);
glibtop_get_mem(&memory);
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


int which,arg;
glibtop_get_proclist(&proclist,which,arg);
printf("%ld\n%ld\n%ld\n",
(unsigned long)proclist.number,
(unsigned long)proclist.total,
(unsigned long)proclist.size);
return 0;
}

