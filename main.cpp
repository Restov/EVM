#include <iostream>
#include "mySimpleComputer.h"
using namespace std;

int main(){
  int RAM[100];
  sc_memoryInit(RAM);
  sc_memorySet(99, 2, RAM);
  int value=0;
  cout << sc_memoryGet(99, value, RAM)<<endl;
  const char *filename = "memory.txt";
  sc_memorySave(filename,RAM);
  sc_memoryInit(RAM);
  sc_memoryLoad(filename, RAM);
  return 0;
}
