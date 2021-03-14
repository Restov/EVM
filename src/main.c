#include "include/mySimpleComputer.h"
#include "include/myTerm.h"
#include "include/myBigChars.h"
#include "include/printConsole.h"
#include "include/myReadkey.h"

int main()
{
    sc_memoryInit();
    sc_memorySet(101, 2);
    sc_regSet(P, 1);
    mt_clrscr();
    printAll();
    enum keys key;
    rk_readkey(&key);
    if(key == key_right){
        mt_setbgcolor(PURPLE);

    }   
    return 0;
}
