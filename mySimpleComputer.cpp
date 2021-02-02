#include "mySimpleComputer.h"
int* sc_memoryInit(int *RAM){
  for(int i =0; i < 100; ++i){
    RAM[i] = 0;
  }
  return RAM;
}
int* sc_memorySet(int address, int value, int *RAM){
  try{
    if(address > 99)
      {
	throw "Out of memory\n";
      }
    RAM[address] = value;
  }
  catch(const char* exception)
    {
      std::cerr << "Error: " << exception << "\n";
    }
  return RAM;
}
int sc_memoryGet(int address, int value, int *RAM){
    try{
    if(address > 99)
      {
	throw "Out of memory\n";
      }
    value = RAM[address];
  }
  catch(const char* exception)
    {
      std::cerr << "Error: " << exception << "\n";
    }
  return value;

}

int sc_memorySave(const char* filename, int* RAM){
  std::ofstream out;
  out.open(filename);
  for(int i = 0; i < 100; ++i){
    out << RAM[i];
  }
  out.close();
  return 0;
}
int sc_memoryload(const char* filename, int* RAM){
  std::ifstream in(filename);
  int reg = 0;
  int i =0;
  while(in.get(reg)){
    RAM[i]=reg;
  }
  in.close();
  return 0;
}
