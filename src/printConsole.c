#include "include/printConsole.h"

static int bcint0[2] = {1717992960, 8283750};
static int bcint1[2] = {471341056, 3938328};
static int bcint2[2] = {538983424, 3935292};
static int bcint3[2] = {2120252928, 8282238};
static int bcint4[2] = {2120640000, 6316158};
static int bcint5[2] = {2114092544, 8273984};
static int bcint6[2] = {33701376, 4071998};
static int bcint7[2] = {811630080, 396312};
static int bcint8[2] = {2120646144, 8283750};
static int bcint9[2] = {2087074816, 3956832};
static int bcintA[2] = {2118269952, 4342338};
static int bcintB[2] = {1044528640, 4080194};
static int bcintC[2] = {37895168, 3949058};
static int bcintD[2] = {1111637504, 4080194};
static int bcintE[2] = {2114092544, 8258050};
static int bcintF[2] = {33717760, 131646};
static int bcintp[2] = {2115508224, 1579134};
static int bcintm[2] = {2113929216, 126};
int time = 0;
int instructionCounter = 0;
void getXY(int *x, int *y)
{
    *x = coord % 10;
    *y = coord / 10;
}

int printInstructionCounterValue()
{
    mt_gotoXY(5, 70);
    printf("+%.4X", instructionCounter);
    return 0;
}

int printAccumulatorValue()
{
    mt_gotoXY(2, 70);
    if (accumulator < 0)
    {
        printf("-%.4X", -accumulator);
    }
    else
    {
        printf("+%.4X", accumulator);
    }
    return 0;
}

int setBGColor(int ind)
{
    int x, y;
    getXY(&x, &y);
    if (ind == 1)
    {
        mt_setbgcolor(BLUE);
        mt_gotoXY(y + 2, (6 + 6 * x) - 4);

        if (RAM[coord] < 0)
        {
            printf("-%.4X", -RAM[coord]);
        }
        else
        {
            printf("+%.4X", RAM[coord]);
        }

        printf("\E[0m");
    }
    else if (ind == 0)
    {
        mt_setbgcolor(LIGHT_GRAY);
        mt_gotoXY(y + 2, (6 + 6 * x) - 4);

        if (RAM[coord] < 0)
        {
            printf("-%.4X", -RAM[coord]);
        }
        else
        {
            printf("+%.4X", RAM[coord]);
        }
    }
    else
    {
        return -1;
    }
    return 0;
}
int resetBG()
{
    setBGColor(0);
    setBGColor(1);
    fflush(stdout);

    return 0;
}
int resetTerm()
{
    mt_clrscr();
    printAll();
    printAccumulatorValue();
    printInstructionCounterValue();
    resetBG();
    printFlags();
    printOperation();
    printCaseBig();
    mt_gotoXY(25, 1);
    for (int i = 0; i < 8; i++)
    {
        for (int i = 0; i < 83; i++)
        {
            printf(" ");
        }
        printf("\n");
    }

    mt_gotoXY(33, 1);
    fflush(stdout);
    return 0;
}
int run()
{
    enum keys key;
    resetTerm();
    sc_memoryInit();
    sc_regInit();
    accumulator = 0;
    coord = 0;
    printAll();
    printAccumulatorValue();
    printInstructionCounterValue();
    signal(SIGUSR1, reset_signalhagle);
    create_timer(1);
    resetTerm();
    char filename[64];
    while (key != key_q)
    {
        rk_readkey(&key);

        switch (key)
        {
        case key_l:

            printf("Enter filename: ");
            rk_mytermregime(0, 0, 1, 1, 1);
            fgets(filename, 63, stdin);
            filename[strlen(filename) - 1] = 0;
            char *ptr1 = strrchr(filename, '.');
 if (ptr1 != NULL)
           {
             if (strcmp(ptr1, ".sa") == 0)
            {
            char *ptr = NULL;
            int size = strlen(filename);
            ptr = malloc(sizeof(char) * size);
            for (int i = 0; i < size; i++)
                ptr[i] = filename[i];
            ptr[size - 1] = 'o';
            ptr[size] = '\0';
            asm_to_object(filename, ptr);
            printf("Asm_to_obj");
            sc_memoryLoad(ptr);
            resetTerm();
             }
            /*else if (strcmp(ptr1, ".sb") == 0)
        {

            char *ptr = NULL;
            int size = strlen(filename);
            ptr = malloc(sizeof(char) * size);
            for (int i = 0; i < size; i++)
                ptr[i] = filename[i];
            ptr[size - 1] = 'a';
            ptr[size] = '\0';
            basic_to_asm(filename, ptr);
            filename[size - 1] = 'o';
            filename[size] = '\0';
            asm_to_object(ptr, filename);
            sc_memoryLoad(filename);
            resetTerm();
        }*/
            else if (strcmp(ptr1, ".so") == 0)
                {
                    sc_memoryLoad(filename);
                    resetTerm();
                }
             }
            break;
        case key_s:
            sc_memorySave("file.txt");
            break;
        case key_r:
            keyRun();
            break;
        case key_tt:
            keyStep();
            break;
        case key_i:
            raise(SIGUSR1);
            break;
        case key_f5:
            keyF5();
            break;
        case key_f6:
            keyF6();
            break;
        case key_up:
            keyUp();
            break;
        case key_down:
            keyDown();
            break;
        case key_right:
            keyRight();
            break;
        case key_left:
            keyLeft();
            break;
        default:

            break;
        }
    }

    return 0;
}
void printOperation()
{
    int x, y;
    getXY(&x, &y);
    int value;
    sc_memoryGet(instructionCounter, &value);
    mt_gotoXY(8, 69);
    int command, operand;
    sc_commandDecode(value, &command, &operand);
    printf("+%.2X : %.2X", command, operand);
}
void keyRun()
{
    sc_regSet(T, 0);
    int x, y;
    getXY(&x, &y);
    setBGColor(0);
    x = 0;
    y = 0;
    coord = 0;
    instructionCounter = 0;
    setBGColor(1);
    sleep(1);
    for (x = 0; x < 10; x++)
    {
        for (y = 0; y < 10; y++)
        {
            keyStep();
            sleep(1);
        }
    }
    sc_regSet(T, 1);
    instructionCounter = 0;
    x = 0;
    y = 0;
    coord = 0;
    setBGColor(1);
    resetTerm();
}
void keyStep()
{
    Cu();
    int x, y;
    getXY(&x, &y);
    //instructionCounter = coord;
    printAccumulatorValue();
    printInstructionCounterValue();
    keyRight();
    resetTerm();
}
void keyF5()
{

    int value = 0;
    sc_memoryGet(coord, &value);
    accumulator = value;
    resetTerm();
    fflush(stdout);
}
void keyF6()
{
    int value = 0;
    sc_memoryGet(coord, &value);
    sc_memorySet(coord, value + 1);
    resetTerm();
    fflush(stdout);
}
void keyRight()
{
    int x, y;
    getXY(&x, &y);

    setBGColor(0);
    if (x != 9)
    {
        x++;
    }
    else if (x == 9 && y != 9)
    {
        x = 0;
        y++;
    }
    setBGColor(1);

    coord = y * 10 + x;
    resetTerm();
}

void keyLeft()
{
    int x, y;
    getXY(&x, &y);

    setBGColor(0);
    if (x != 0)
    {
        x--;
    }
    else if (x == 0 && y != 0)
    {
        x = 9;
        y--;
    }
    setBGColor(1);

    coord = y * 10 + x;
    resetTerm();
}

void keyUp()
{
    int x, y;
    getXY(&x, &y);

    if (y != 0)
    {
        setBGColor(0);
        y--;
        setBGColor(1);
    }

    coord = y * 10 + x;
    resetTerm();
}
void keyDown()
{
    int x, y;
    getXY(&x, &y);

    if (y != 9)
    {
        setBGColor(0);
        y++;
        setBGColor(1);
    }

    coord = y * 10 + x;
    resetTerm();
}
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
    char r_P = ' ', r_O = ' ', r_M = ' ', r_T = ' ', r_E = ' ';
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

int printOperationbox()
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

int printCaseBig()
{
    int value;
    int rank[4];
    int x, y;
    int column = 46;
    int row = 10;
    bc_box(BOX_ROW_MEMORY + 1, 1, row, column);
    getXY(&x, &y);

    sc_memoryGet(y * 10 + x, &value);

    if (value < 0)
    {
        bc_printbigchar(bcintm, 13, 2, BLACK, RED);
        value *= -1;
    }
    else
    {
        bc_printbigchar(bcintp, 13, 2, BLACK, RED);
    }

    for (int i = 0; i < 4; ++i)
    {
        rank[i] = value % 16;
        value /= 16;
    }

    for (int i = 38, j = 0; i >= 11; i -= 9, j++)
        printBigChars(rank[j], i);

    return 0;
}

int printBigChars(int val, int k)
{
    switch (val)
    {
    case 0:
        bc_printbigchar(bcint0, 13, k, BLACK, RED);
        break;
    case 1:
        bc_printbigchar(bcint1, 13, k, BLACK, RED);
        break;
    case 2:
        bc_printbigchar(bcint2, 13, k, BLACK, RED);
        break;
    case 3:
        bc_printbigchar(bcint3, 13, k, BLACK, RED);
        break;
    case 4:
        bc_printbigchar(bcint4, 13, k, BLACK, RED);
        break;
    case 5:
        bc_printbigchar(bcint5, 13, k, BLACK, RED);
        break;
    case 6:
        bc_printbigchar(bcint6, 13, k, BLACK, RED);
        break;
    case 7:
        bc_printbigchar(bcint7, 13, k, BLACK, RED);
        break;
    case 8:
        bc_printbigchar(bcint8, 13, k, BLACK, RED);
        break;
    case 9:
        bc_printbigchar(bcint9, 13, k, BLACK, RED);
        break;
    case 10:
        bc_printbigchar(bcintA, 13, k, BLACK, RED);
        break;
    case 11:
        bc_printbigchar(bcintB, 13, k, BLACK, RED);
        break;
    case 12:
        bc_printbigchar(bcintC, 13, k, BLACK, RED);
        break;
    case 13:
        bc_printbigchar(bcintD, 13, k, BLACK, RED);
        break;
    case 14:
        bc_printbigchar(bcintE, 13, k, BLACK, RED);
        break;
    case 15:
        bc_printbigchar(bcintF, 13, k, BLACK, RED);
        break;
    }
    return 0;
}

int printAll()
{
    printMemory();
    printInstructionCounter();
    printOperationbox();
    printAccumulator();
    printFlags();
    //printBigChars();
    printKeys();
    return 0;
}