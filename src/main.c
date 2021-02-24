#include "include/mySimpleComputer.h"
#include "include/myTerm.h"
#include "include/myBigChars.h"
#include "include/printConsole.h"

int main()
{
    sc_memoryInit();
    sc_memorySet(101, 2);
    sc_regSet(P, 1);
    mt_clrscr();
    printMemory();
    printFlags();
    printKeys();
    //mt_clrscr();
    return 0;
}
