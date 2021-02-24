#ifndef MYBIGCHARS
#define MYBIGCHARS
#pragma once

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "myTerm.h"

/*
    enter_alt_charset_mode=^N
    exit_alt_charset_mode=^O
    acs_chars=++\054\054--..00__``aaffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}c~~
*/

#define BC_ANGLE_LEFT_UP "l"
#define	BC_ANGLE_LEFT_DOWN "m"
#define	BC_ANGLE_RIGHT_UP "k"
#define	BC_ANGLE_RIGHT_DOWN "j"
#define	BC_LINE_VERTICAL "x"
#define	BC_LINE_HORIZONTAL "q"
#define	BC_CAGED_CELL "a"

#define EN_MACS "\E(0"
#define EX_MACS "\E(B"

#define BLACK_CHAR 'a'

int bc_printA (const char * str);

int bc_box(int x1, int y1, int x2, int y2);

int bc_printbigchar(int arr[2], int x, int y, enum colors b_col, enum colors f_col);

#endif