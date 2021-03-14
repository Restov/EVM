#include "include/myReadkey.h"

int rk_readkey(enum keys *key)
{
    rk_mytermregime(0, 0, 1, 1, 0);
    char buff[8] = {0};
    read(STDIN_FILENO, buff, 8);
    if (strcmp(buff, "\E[A") == 0)
    {
        *key = key_up;
    }
    else if (strcmp(buff, "\E[B") == 0)
    {
        *key = key_down;
    }
    else if (strcmp(buff, "\E[C") == 0)
    {
        *key = key_right;
    }
    else if (strcmp(buff, "\E[D") == 0)
    {
        *key = key_left;
    }
    else if (strcmp(buff, "\E[[E") == 0)
    {
        *key = key_f5;
    }
    else if (strcmp(buff, "\E[17~") == 0)
    {
        *key = key_f6;
    }
    else if (buff[0] == 'l')
    {
        *key = key_l;
    }
    else if (buff[0] == 's')
    {
        *key = key_s;
    }
    else if (buff[0] == 'r')
    {
        *key = key_r;
    }
    else if (buff[0] == 't')
    {
        *key = key_t;
    }
    else if (buff[0] == 'i')
    {
        *key = key_i;
    }
    else if (buff[0] >= '0' && buff[0] <= '9')
    {
        *key = buff[0] - 48;
    }
    else if (buff[0] == 'q')
    {
        *key = key_q;
    }
    else
    {
        *key = key_other;
    }
    rk_mytermrestore();
    return 0;
}

int rk_mytermsave(void)
{
    FILE *f = fopen("attributes", "wb");
    if (tcgetattr(STDIN_FILENO, &atr) != 0)
        return -1;
    fwrite(&atr, sizeof(atr), 1, f);
    fclose(f);
    return 0;
}
int rk_mytermrestore(void)
{
    FILE *f;
    if ((f = fopen("attributes", "rb")) == NULL)
        return -1;
    if (fread(&atr, sizeof(atr), 1, f) == -1)
    {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &atr) != 0)
            return -1;
    }
    else
    {
        return -1;
    }
    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios newatr;
    rk_mytermsave();
    if (regime == 1)
    {
        newatr.c_lflag |= ICANON;
    }
    else if (regime == 0)
    {
        if (echo == 1)
        {
            newatr.c_lflag |= ECHO;
        }
        else if (echo == 0)
        {
            newatr.c_lflag &= (~ECHO);
        }
        if (sigint == 1)
        {
            newatr.c_lflag |= ISIG;
        }
        else if (sigint == 0)
        {
            newatr.c_lflag &= (~ISIG);
        }
        newatr.c_cc[VTIME] = vtime;
        newatr.c_cc[VMIN] = vmin;
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &newatr);
    return 0;
}