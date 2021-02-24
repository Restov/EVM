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

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int printMemory();
int printFlags();
int printKeys();


#endif