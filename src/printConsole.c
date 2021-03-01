#include "include/printConsole.h"

static int bcint0 [2] = {1717992960, 8283750};
// static int bcint1 [2] = {471341056, 3938328};
// static int bcint2 [2] = {538983424, 3935292};
// static int bcint3 [2] = {2120252928, 8282238};
// static int bcint4 [2] = {2120640000, 6316158};
// static int bcint5 [2] = {2114092544, 8273984};
// static int bcint6 [2] = {33701376, 4071998};
// static int bcint7 [2] = {811630080, 396312};
// static int bcint8 [2] = {2120646144, 8283750};
// static int bcint9 [2] = {2087074816, 3956832};
// static int bcintA [2] = {2118269952, 4342338};
// static int bcintB [2] = {1044528640, 4080194};
// static int bcintC [2] = {37895168, 3949058};
// static int bcintD [2] = {1111637504, 4080194};
// static int bcintE [2] = {2114092544, 8258050};
// static int bcintF [2] = {33717760, 131646};
static int bcintp [2] = {2115508224, 1579134};
// static int bcintm [2] = {2113929216, 126};

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

int printAccumulator()
{
	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	return 0;
}

int printInstructionCounter()
{
	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	return 0;
}

int printOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(7, 68);
	printf(" Operation ");
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

int printBigChars(){
    bc_printbigchar(bcintp, 13, 1, BLACK, RED);
    for (int i = 0, k = 9; i < 4; i++, k+=8)
    {
        bc_printbigchar(bcint0, 13, k, BLACK, RED);
    }
    return 0;
}

int printAll()
{
    printMemory();
    printInstructionCounter();
    printOperation();
    printAccumulator();
    printFlags();
    printBigChars();
    printKeys();
    return 0;
}