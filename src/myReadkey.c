#include "include/myReadkey.h"


int rk_readkey(enum keys *key)
{

    
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
    return 0;
}

int rk_mytermsave(void){
    FILE *f = fopen("attributes", "wb");
	fwrite(&atr,sizeof(atr),1,f);
	fclose(f);
	return 0;
}
int rk_mytermrestore(void){
    FILE *f;
    if ((f=fopen("attributes","rb"))==NULL)
		return -1;
    fread(&atr,sizeof(atr),1,f);
    return 0;
}