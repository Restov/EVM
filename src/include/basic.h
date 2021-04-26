#ifndef BASIC_H
#define BASIC_H
#pragma once
#include <string.h>
#include <ctype.h>
#include "rpn.h"
#include "myTerm.h"
#include <unistd.h>

struct stack_t {
    char c;
    struct stack_t *next;
};

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
};


struct stack_t *stack_push(struct stack_t *head, char a);
char stack_pop(struct stack_t **head);
int get_prior(char c);
void translate_to_rpn(char *outstr, char *a);
int command_type(const char *cmd);
unsigned variable_id(const struct stVariables *vars, unsigned max, char var);
int basic_to_asm(const char* filename_bas, const char* filename_asm);

#endif 
