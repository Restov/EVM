#include "include/myTerm.h"

/*
    clear_screen=\E[H\E[J
    cursor_address=\E[%i%p1%d;%p2%dH
    set_a_background=\E[4%p1%dm
    set_a_foreground=\E[3%p1%dm
    cursor_invisible=\E[?25l\E[?1c
    cursor_visible=\E[?25h\E[?8c
*/

int mt_clrscr(void)
{
    return printf("\E[H\E[J");
}

int mt_gotoXY(int y, int x)
{
    return printf("\E[%d;%dH", y, x);
}

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize ws;
    if (!ioctl(1, TIOCGWINSZ, &ws))
    {
        //printf("\nПолучен размер экрана.\n");
        *rows = ws.ws_row, *cols = ws.ws_col;
        //printf("Число строк–%d\nЧисло столбцов–%d\n", *rows, *cols);
        return 0;
    }
    else
    {

        return -1;
    }
}

int mt_setfgcolor(enum colors color)
{
    return printf("\E[3%dm", color);
}

int mt_setbgcolor(enum colors color)
{
    return printf("\E[4%dm", color);
}

int mt_defcolor()
{
    printf("\E[0m");
    return 0;
}