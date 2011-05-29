 
# Will be using g++ to compile the files.
CC=g++

CFLAGS=-c -Wall -fexceptions -g -Wall
#Needed for adding Glib
GLibCFLAG = `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -I/usr/include/libgtop-2.0 -lgtop-2.0

all: sysinfox

sysinfox: main.o sysinfo.o
	$(CC) $(GLibCFLAG) main.o sysinfo.o -o sysinfox

main.o: main.cpp
	$(CC) $(CFLAGS) $(GLibCFLAG) main.cpp

sysinfo.o: sysinfo.cpp
	g++ $(CFLAGS) $(GLibCFLAG) sysinfo.cpp


clean:
	rm -rf *.o sysinfox