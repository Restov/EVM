#ifndef MYREADKEY
#define MYREADKEY

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
	key_t,
	key_i,
    key_q,
	key_other,
};

int rk_readkey(enum keys*);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif