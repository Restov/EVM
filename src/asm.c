#include "include/asm.h"


int asm_to_object(const char* filename_asm, const char* filename_object) {
    FILE *fasm = fopen(filename_asm, "r");
    if (!fasm)
        return 1;
    int address, operand, code, encode, ignore;
    char cmd[16] = { 0 };
    while (fscanf(fasm,"%d %[=a-zA-Z]", &address, cmd) != 0) {
        if (cmd[0] != '=') {
            fscanf(fasm, "%d", &operand);
            code = cmd_search(cmd);
            if (code == -1 || sc_commandEncode(code, operand, &encode))
                return 1;
        } else {
            fscanf(fasm, "%x", &encode);
            encode = 0x4000 | (encode & 0x3FFF);
        }
        sc_memorySet(address, encode);
        do { ignore = fgetc(fasm); }
        while (ignore != '\n' && ignore != EOF);
        if (ignore == EOF)
            break;
    }
    fclose(fasm);
    if (cmd[0] == 0)
        return 1;
    sc_memorySave(filename_object);
    return 0;
}
