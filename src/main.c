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

    int temp()
    {
        int accumulator = 0;
        mt_gotoXY(2, 70);
            if (accumulator < 0)
            {
                printf("-%.4X", -accumulator);
            }
            else
            {
                printf("+%.4X", accumulator);
            }
            mt_gotoXY(72, 0);
        return 0;
    }

    while (key != key_q)
    {
        rk_readkey(&key);
        switch (key)
        {
        case key_down:

            break;

        case key_s:
            sc_memorySave("file.txt");
            break;

        case key_l:
            sc_memoryLoad("file.txt");
            break;

        case key_up:
            temp();
            break;

        default:
            break;
        }
    }

    return 0;
}
