#include "include/asm.h"

int cmd_search(const char *command)
{
    if (strcmp(command, "READ")== 0) return 0x10;
    else if (strcmp(command, "WRITE")==0) return 0x11;
    else if (strcmp(command, "LOAD")==0) return 0x20;
    else if (strcmp(command, "STORE")==0) return 0x21;
    else if (strcmp(command, "ADD")==0) return 0x30;
    else if (strcmp(command, "SUB")==0) return 0x31;
    else if (strcmp(command, "DIVIDE")==0) return 0x32;
    else if (strcmp(command, "MUL")==0) return 0x33;
    else if (strcmp(command, "JUMP")==0) return 0x40;
    else if (strcmp(command, "JNEG")==0) return 0x41;
    else if (strcmp(command, "JZ")==0) return 0x42;
    else if (strcmp(command, "HALT")==0) return 0x43;
    else if (strcmp(command, "JNP")==0) return 0x59;
    return -1;
}

int asm_to_object(const char *filename_asm, const char *filename_object)
{
    FILE *fasm = fopen(filename_asm, "r");
    if (!fasm)
        return 1;
    int address, operand, code, encode, ignore;
    char cmd[16] = {0};
    while (fscanf(fasm, "%d %[=a-zA-Z]", &address, cmd) != 0)
    {
        if (cmd[0] != '=')
        {
            fscanf(fasm, "%d", &operand);
            code = cmd_search(cmd);
            if (code == -1 || sc_commandEncode(code, operand, &encode))
                return 1;
        }
        else
        {
            fscanf(fasm, "%x", &encode);
            encode = 0x4000 | (encode & 0x3FFF);
        }
        sc_memorySet(address, encode);
        do
        {
            ignore = fgetc(fasm);
        } while (ignore != '\n' && ignore != EOF);
        if (ignore == EOF)
            break;
    }
    fclose(fasm);
    if (cmd[0] == 0)
        return 1;
    sc_memorySave(filename_object);
    return 0;
}
