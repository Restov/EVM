#include "include/mySimpleComputer.h"

int RAM[100];

int flag;

int sc_memoryInit() {
    for (int i = 0; i < SIZE; ++i) {
        RAM[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address >= SIZE || address < 0) {
        return 1;
    }
    RAM[address] = value;

    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address >= SIZE || address < 0) {
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

int sc_commandEncode(int command, int operand, int *value)
{
	if ((operand > 0x7F || operand < 0x0) &&
        (command != (0x10 || 0x11 || 0x20 || 0x21 || 0x30 || 0x31 || 0x32 || 0x33 || 0x40 || 0x41 || 0x42 || 0x43 ||
        0x51 || 0x52 || 0x53 || 0x54 || 0x55 || 0x56 || 0x57 || 0x58 || 0x59 || 0x60 || 0x61 || 0x62 || 0x63 || 
        0x64 || 0x65 || 0x66 || 0x67 || 0x68 || 0x69 || 0x70 || 0x71 || 0x72 || 0x73 || 0x74 || 0x75 || 0x76))) {
            return 1;
	}

	*value = (command << 7) | operand;

	return 0;
}

int sc_commandDecode(int value, int *command, int *operand)
{
	if ((value >> 14) != 0) {
		return 1;
	}

	*command = value >> 7;
	*operand = value & 0x7F;
	return 0;
}
