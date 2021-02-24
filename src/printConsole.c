#include "include/printConsole.h"

int printMemory()
{
    bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);
	mt_gotoXY(1, 28);
	printf(" Memory ");
    for (int i = 0; i < 10; i++)
    {
        mt_gotoXY(2 + i, 2);
        for (int j = 0; j < 10; j++)
        {
            if (j != 0)
                printf(" ");
            if (RAM[i * 10 + j] < 0)
            {
                printf("-%.4X", -RAM[i * 10 + j]);
            }
            else
            {
                printf("+%.4X", RAM[i * 10 + j]);
            }
        }
    }
    printf("\n");
    return 0;
}

int printFlags()
{
    int reg_p, reg_o, reg_m, reg_t, reg_e;
    char r_P=' ', r_O=' ', r_M=' ', r_T=' ', r_E=' ';
    sc_regGet(P, &reg_p);
    sc_regGet(O, &reg_o);
    sc_regGet(M, &reg_m);
    sc_regGet(T, &reg_t);
    sc_regGet(E, &reg_e);
    if (reg_p == 1)
        r_P = 'P';
    if (reg_o == 1)
        r_O = 'O';
    if (reg_m == 1)
        r_M = 'M';
    if (reg_t == 1)
        r_T = 'T';
    if (reg_e == 1)
        r_E = 'E';
    mt_gotoXY(11, 64);
    printf("%c %c %c %c %c\n", r_P, r_O, r_M, r_T, r_E);
    mt_gotoXY(11, 62);
    bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(10, 69);
	printf(" Flags ");
    return 0;
}

int printKeys()
{
	int column = 37;
	 int row = 10;

	bc_box(13, 47, row, column);
	mt_gotoXY(13, 48);
	printf(" Keys: ");
	mt_gotoXY(14, 48);
	printf("l   - load");
	mt_gotoXY(15, 48);
	printf("s   - save");
	mt_gotoXY(16, 48);
	printf("r   - run");
	mt_gotoXY(17, 48);
	printf("t   - step");
	mt_gotoXY(18, 48);
	printf("i   - reset");
	mt_gotoXY(19, 48);
	printf("F5  - accumulator");
	mt_gotoXY(20, 48);
	printf("F6  - instructionCounter");
	mt_gotoXY(21, 48);
	printf("q   - exit\n\n");
	return 0;
}