#ifndef BASIC_H
#define BASIC_H
#pragma once
#include <string.h>
#include <ctype.h>
#include "rpn.h"

struct stLines {
    unsigned line_number;
    unsigned start_address;
};

struct stVariables {
    unsigned address;
    int init_value;
    char name;
};

struct stGotoConflict {
    unsigned instratuction_address;
    unsigned goto_line;
    char calc;
};

int command_type(const char *cmd);
unsigned variable_id(const struct stVariables *vars, unsigned max, char var);
int basic_to_asm(const char* filename_bas, const char* filename_asm);

#endif 
