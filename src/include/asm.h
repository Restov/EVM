#ifndef ASM
#define ASM
#include <stdio.h>
#include <string.h>
#include "cu.h"

int cmd_search(const char *command);
int asm_to_object(const char *filename_asm, const char *filename_object);

#endif