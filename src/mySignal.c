#include "include/mySignal.h"

void signalhangle(int signal) {
    int val;
    sc_regGet(T, &val);
    if (val == 0) {
        Cu();
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
    sc_regSet(T, 1);
    sc_memoryInit();
    resetTerm();
}

void create_timer(double interval) {
    struct itimerval nval;
    nval.it_value.tv_sec = nval.it_interval.tv_sec = (long)interval;
    nval.it_value.tv_usec = nval.it_interval.tv_usec = (long)((interval - (long)interval) * 1000000);
    setitimer (ITIMER_REAL, &nval, NULL);
}
