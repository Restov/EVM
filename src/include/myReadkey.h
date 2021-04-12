#ifndef MYREADKEY
#define MYREADKEY

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

enum keys{
	key_up = 10,
	key_down,
	key_right,
	key_left,
	key_f5,
	key_f6,
	key_l,
	key_s,
	key_r,
	key_tt,
	key_i,
    key_q,
	key_other,
};
struct termios atr;
int rk_readkey(enum keys*);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif