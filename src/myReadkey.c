#include "include/myReadkey.h"


int rk_readkey(enum keys *key)
{

    char buf[8] = {0};
    read(STDIN_FILENO, buf);
    if (strcmp(buf, "\E[A") == 0)
    {
        *key = key_up;
    }
    else if (strcmp(buf, "\E[B") == 0)
    {
        *key = key_down;
    }
    else if (strcmp(buf, "\E[C") == 0)
    {
        *key = key_right;
    }
    else if (strcmp(buf, "\E[D") == 0)
    {
        *key = key_left;
    }
    else if (strcmp(buf, "\E[[E") == 0)
    {
        *key = key_f5;
    }
    else if (strcmp(buf, "\E[17~") == 0)
    {
        *key = key_f6;
    }
    else if (buf[0] == 'l')
    {
        *key = key_l;
    }
    else if (buf[0] == 's')
    {
        *key = key_s;
    }
    else if (buf[0] == 'r')
    {
        *key = key_r;
    }
    else if (buf[0] == 't')
    {
        *key = key_t;
    }
    else if (buf[0] == 'i')
    {
        *key = key_i;
    }
    else if (buf[0] >= '0' && buf[0] <= '9')
    {
        *key = buf[0] - 48;
    }
    else if (buf[0] == 'q')
    {
        *key = key_q;
    }
    else
    {
        *key = key_other;
    }
}
