#ifndef MYTERM
#define MYTERM
#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>


enum colors {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    BROWN = 3,
    BLUE = 4,
    PURPLE = 5,
    CYAN = 6,
    LIGHT_GRAY  = 7,
};

void escape_commands();

int mt_clrscr(void);

int mt_gotoXY(int y, int x);

int mt_getscreensize(int *rows, int *cols);

int mt_setfgcolor(enum colors color);

int mt_setbgcolor(enum colors color);


#endif
