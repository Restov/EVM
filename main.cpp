#include "mySimpleComputer.h"

using namespace std;

int main() {
    sc_memoryInit();
    sc_memorySet(99, 2);
    int value = 0;
    cout << sc_memoryGet(99, &value) << endl;
    cout << value;
    const char *filename = "memory.txt";
    sc_memorySave(filename);
    sc_memoryInit();
    sc_memoryLoad(filename);
    return 0;
}
