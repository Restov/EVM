#ifndef PRINTCONSOLE
#define PRINTCONSOLE
#pragma once

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "mySignal.h"
#include "cu.h"
#include "asm.h"
#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22
int coord;
int accumulator;
extern int instructionCounter;
char io_msg[1024];
void log_console(const char *msg);
void read_console_value(int addr, int *value);
int write_console_value(int addr, int value);
int printMemory();
void getXY(int *x, int *y);
int printInstructionCounter();
int printAccumulatorValue();
int setBGColor(int ind);
int resetBG();
int resetTerm();
int printInstructionCounterValue();
int run();
int printCaseBig();
int printFlags();
int printAccumulator();
void keyUp();
void keyDown();
void keyRight();
void keyLeft();
void keyF5();
void keyF6();
void keyStep();
void keyRun();
void printOperation();
int printOperationbox();
void keyLoad();
void key_num();
void printComs();
void keyLoad();
void keySave();
int printKeys();
int printBigChars();
int printAll();

#endif