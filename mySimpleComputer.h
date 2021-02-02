#ifndef MYSIMPLECOMPUTER
#define MYSIMPLECOMPUTER
#include <iostream>
#include <fstream>

int* sc_memoryInit(int *RAM);
int* sc_memorySet(int address, int value, int *RAM);
int sc_memoryGet(int address, int value, int *RAM);
int sc_memorySave(const char* filename, int* RAM);
int sc_memoryload(const char* filename, int* RAM);

#endif
