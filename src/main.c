#include "include/printConsole.h"


int main()
{
    run();
    return 0;
}
// #include <stdio.h>
// #include <signal.h>
// #include <sys/time.h>
// void signalhandler (int signo){
//     printf ("Сработал таймер\n");
// }
// int main (void)
// {
//     struct itimerval nval, oval;
//     signal (SIGALRM, signalhandler);
//     nval.it_interval.tv_sec = 3;
//     nval.it_interval.tv_usec = 500;
//     nval.it_value.tv_sec = 1;
//     nval.it_value.tv_usec = 0;
//     setitimer (ITIMER_REAL, &nval, &oval);
//     while (1){
//         //pause();
//     }
//     return (0);
// }