#ifndef PRINTCONSOLE
#define PRINTCONSOLE
#pragma once

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22
int coord;
int accumulator;
int printMemory();
void getXY(int *x, int *y);
int printInstructionCounter();
int printAccumulatorValue();
int setBGColor(int ind);
int resetBG();
int resetTerm();
int printInstructionCounterValue();
int run();
int printFlags();
int printAccumulator();
void keyUp();
void keyDown();
void keyRight();
void keyLeft();
void keyF5();
void keyF6();
int printOperation();
int printKeys();
int printBigChars();
int printAll();

#endif