CC=gcc
CXX = g++  # C compiler
CXXFLAGS = -Wall -Wextra -L. -g #-O2 -g  # C flags
LDFLAGS = -fPIC -shared # linking flags
CLINK=$(CC)
CFLAGS=-g -Wall -std=c99
RM=rm -rf *.o *.exe libfirewall.so

all: firewall.exe

firewall: 
	$(CXX) ${CXXFLAGS} ${LDFLAGS} string.cpp field.cpp ip.cpp port.cpp \
	-o libfirewall.so

firewall.exe: firewall
	$(CXX) ${CXXFLAGS} main.cpp -o firewall.exe -lfirewall -linput

clean:
	$(RM)