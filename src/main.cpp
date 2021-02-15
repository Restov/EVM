#include "include/mySimpleComputer.h"
#include "include/myTerm.h"

using namespace std;

int main()
{
    sc_memoryInit();
    sc_memorySet(99, 2);
    int value = 0;
    sc_memoryGet(99, &value);
    cout << "memory get = " << value << endl;
    const char *filename = "memory.txt";
    sc_memorySave(filename);
    cout << "memory save = " << RAM[99] << endl;
    sc_memoryInit();
    cout << "memory init = " << RAM[99] << endl;
    sc_memoryLoad(filename);
    cout << "memory load = " << RAM[99] << endl;
    sc_regInit();
    cout << "reg init = " << flag << endl;
    value = 1;
    sc_regSet(P, value);
    cout << "reg set = " << flag << endl;
    sc_regGet(P, &value);
    cout << "reg get = " << value << endl;
    value = 0;
    int com = 0x10, op = 0x1;
    int *command = &com, *operand = &op;
    sc_commandEncode(*command, *operand, &value);
    cout << "\nencode = " << value << endl;
    sc_commandDecode(value, command, operand);
    cout << "\ndecode = " << value << endl;
    //mt_gotoXY(100, 20);
    //mt_setbgcolor(BLACK);
    //mt_setfgcolor(RED);
    int rows = 0, cols = 0;
    mt_getscreensize(&rows, &cols);
    escape_commands();
    //mt_clrscr();
    return 0;
}
