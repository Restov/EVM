#include "include/mySignal.h"

void signalhangle(int signal) {
    int val;
    sc_regGet(T, &val);
    if (val == 0) {
        ++instructionCounter;
        resetTerm();
    }           
}

void reset_signalhagle(int signal){
    accumulator = 0;
    instructionCounter = 0;
    setBGColor(0);
    coord = 0;
    setBGColor(1);
    sc_regInit();
    sc_memoryInit();
    resetTerm();
}

void create_timer(unsigned int interval) {
    struct itimerval nval, oval;
	signal (SIGALRM, signalhangle);

	nval.it_interval.tv_sec = interval;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	/* Запускаем таймер */
	setitimer (ITIMER_REAL, &nval, &oval);
}

