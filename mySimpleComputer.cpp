#include "mySimpleComputer.h"

int sc_memoryInit() {
    for (int i = 0; i < 100; ++i) {
        RAM[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address > SIZE || address < 0) {
        return 1;
    }
    RAM[address] = value;

    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address > SIZE || address < 0) {
        return 1;
    }
    *value = RAM[address];

    return 0;
}

int sc_memorySave(const char *filename) {
    FILE *mem_file = fopen(filename, "wb");
    fwrite(RAM, sizeof(int), SIZE, mem_file);
    fclose(mem_file);

    return 0;
}

int sc_memoryLoad(const char *filename) {
    FILE *mem_file = fopen(filename, "rb");
    fread(RAM, sizeof(int), SIZE, mem_file);
    fclose(mem_file);

    return 0;
}

int sc_regInit() {
    flag = 0;
    return 0;
}

int sc_regSet(int reg, int value) {
    if (reg == P || reg == O || reg == M || reg == T || reg == E) {
        if (value == 0) {
            flag = flag & ~reg;
        } else if (value == 1) {
            flag = flag | reg;
        } else {
            return 0;
        }
    }
    return 0;
}

int sc_regGet(int reg, int *value) {
    if (reg == P || reg == O || reg == M || reg == T || reg == E) {
        if ((flag & reg) != 0) {
            *value = 1;
        } else {
            *value = 0;
        }
    }
    return 0;
}