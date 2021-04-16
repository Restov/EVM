#ifndef CU
#define CU
#include "printConsole.h"

#define READ 0x10
#define WRITE 0x11
#define LOAD 0x20
#define STORE 0x21
#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33
#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43
#define JNP 0x59
#define JNS 0x55

int Cu();
int Alu(int command, int operand);

#endif