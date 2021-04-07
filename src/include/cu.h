#ifndef CU
#define CU
#include "printConsole.h"
#define READ 0x10 
#define WRITE 0X11
#define LOAD 0X20
#define STORE 0X21
#define ADD 0X30
#define SUB 0X31
#define DIVIDE 0X32
#define MUL 0X33
#define JUMP 0X40
#define JNEG 0X41
#define JZ 0x42
#define HALT 0x43
#define JNP 0x59
int Cu();
int Alu(int command, int operand);

#endif