#include "include/basic.h"

struct stack_t *stack_push(struct stack_t *head, char a)
{
    struct stack_t *ptr;

    if ((ptr = malloc(sizeof(struct stack_t))) == NULL)
    {
        perror("Out of memory\n");
        exit(1);
    }
    ptr->c = a;
    ptr->next = head;
    return ptr;
}

char stack_pop(struct stack_t **head)
{
    struct stack_t *ptr;
    char a;

    if (*head == NULL)
        return '\0';
    ptr = *head;
    a = ptr->c;
    *head = ptr->next;
    free(ptr);
    return a;
}

int get_prior(char c)
{
    switch (c)
    {
    case '*':
        return 3;
    case '/':
        return 3;
    case '-':
        return 2;
    case '+':
        return 2;
    case '(':
        return 1;
    default:
        break;
    }
    return 0;
}

void translate_to_rpn(char *outstr, char *a)
{
    struct stack_t *opers = NULL;
    int k, point;

    k = 0;
    point = 0;
    while (a[k] != '\0' && a[k] != '\n')
    {
        if (a[k] == ')')
        {
            while ((opers->c) != '(')
                outstr[point++] = stack_pop(&opers);
            stack_pop(&opers);
        }
        if ((a[k] >= 'A' && a[k] <= 'Z') || (a[k] >= '0' && a[k] <= '9'))
            outstr[point++] = a[k];
        else if (a[k] == '(')
            opers = stack_push(opers, '(');
        else if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*')
        {
            if (opers == NULL)
                opers = stack_push(opers, a[k]);
            else if (get_prior(opers->c) < get_prior(a[k]))
                opers = stack_push(opers, a[k]);
            else
            {
                while ((opers != NULL) && (get_prior(opers->c) >= get_prior(a[k])))
                    outstr[point++] = stack_pop(&opers);
                opers = stack_push(opers, a[k]);
            }
        }
        k++;
    }
    while (opers != NULL)
        outstr[point++] = stack_pop(&opers);
    outstr[point] = '\0';
}

int command_type(const char *cmd) {
    if (!strcmp(cmd, "REM"))
        return 1;
    if (!strcmp(cmd, "INPUT"))
        return 2;
    if (!strcmp(cmd, "PRINT"))
        return 3;
    if (!strcmp(cmd, "GOTO"))
        return 4;
    if (!strcmp(cmd, "IF"))
        return 5;
    if (!strcmp(cmd, "LET"))
        return 6;
    if (!strcmp(cmd, "END"))
        return 7;
    
    return 0;
}

unsigned variable_id(const struct stVariables *vars, unsigned max, char var) { // существует ли переменная с таким именем
    unsigned id = 0;
    for (; id < max; ++id)
        if (vars[id].name == var)
            return id;
    return max;
}

#define getVarID(toID, varName) \
if (isdigit(varName)) { \
    toID = var_id; \
    var[toID].name = tmp_var; \
    var[toID].address = 99 - toID; \
    var[toID].init_value = atoi(&varName); \
    ++var_id; \
    ++tmp_var; \
} else { \
    toID = variable_id(var, var_id, varName); \
    if (toID == var_id) { \
        var[toID].name = varName; \
        var[toID].address = 99 - toID; \
        var[toID].init_value = 0; \
        ++var_id; \
    } \
}

int basic_to_asm(const char* filename_bas, const char* filename_asm) {
    FILE *fbas = fopen(filename_bas, "r");
    if (!fbas) return 1;

    char *asm_code = (char *) malloc(100 * 16);
    asm_code[0] = 0;
    struct stLines *lines = (struct stLines *) malloc(sizeof(*lines) * 100); // массив соответствия строк
    struct stVariables *var = (struct stVariables *) malloc(sizeof(*var) * 52);
    struct stGotoConflict *_goto = (struct stGotoConflict *) malloc(sizeof(*_goto) * 100);

    char *buffer = (char *) malloc(128);
    unsigned address = 0; // номер строки в ассемблере
    unsigned goto_id = 0;
    unsigned var_id = 0; // текущая переменная в программе
    unsigned line = 0; // текущий номер строки basic (10/20/30)
    unsigned line_id = 0; // её айди в массиве lines
    char fail = 0, end = 0, tmp_var/*для инициализаций чисел которые не являются переменными*/ = 'a';

    //A-Z - basic variables
    //a-z - temp variables

    while (end == 0 && fscanf(fbas, "%u %[A-Z] ", &line, buffer) != 0) {
        if (line_id != 0 && line <= lines[line_id].line_number) { // проверка что строки идут по возрастанию
            end = fail = 1;
            break;
        }
        int type = command_type(buffer);
        lines[line_id].line_number = line;
        lines[line_id].start_address = address;  // начало строки basic в assembler
        ++line_id;
        type_check:
        switch (type) {
            case 0:
                fail = 1;
                break;
            case 1:
                continue;
            case 2: {
                fscanf(fbas, "%[A-Z]", buffer);
                if (buffer[1] != 0 || !(buffer[0] >= 'A' && buffer[0] <= 'Z')) {
                    end = fail = 1;
                    break;
                }
                unsigned id = variable_id(var, var_id, buffer[0]);
                if (id == var_id) {
                    var[id].name = buffer[0];
                    var[id].address = 99 - id;
                    var[id].init_value = 0;
                    ++var_id;
                }
                sprintf(buffer, "%02u READ %02u\n", address, var[id].address);
                strcat(asm_code, buffer);
            }
                break;
            case 3: {
                fscanf(fbas, "%[A-Z]", buffer);
                if (buffer[1] != 0 || !(buffer[0] >= 'A' && buffer[0] <= 'Z')) {
                    end = fail = 1;
                    break;
                }
                unsigned id = variable_id(var, var_id, buffer[0]);
                if (id == var_id) {
                    var[id].name = buffer[0];
                    var[id].address = 99 - id;
                    var[id].init_value = 0;
                    ++var_id;
                }
                sprintf(buffer, "%02u WRITE %02u\n", address, var[id].address);
                strcat(asm_code, buffer);
            }
                break;
            case 4: {
                sprintf(buffer, "%02u JUMP ", address);
                strcat(asm_code, buffer);
                fscanf(fbas, "%u", &line);
                if (line > lines[line_id - 1].line_number)  {
                    _goto[goto_id].goto_line = line;
                    _goto[goto_id].instratuction_address = strlen(asm_code);
                    strcat(asm_code, "00\n");
                    ++goto_id;

                    ++address;
                    continue;
                }
                int id = line_id - 1;
                while (id >= 0 && line != lines[id].line_number)
                    --id;
                if (id < 0) {
                    end = fail = 1;
                    break;
                }
                sprintf(buffer, "%02u\n", lines[id].start_address);
                strcat(asm_code, buffer);
            }
                break;
            case 5: {
                char op1[8], op2[8];
                fscanf(fbas, "%[0-9A-Z] %1[<=>] %[0-9A-Z]", op1, buffer, op2);
                if (isdigit(op1[0]) && isdigit(op2[0])) {
                    int result = 0;
                    switch (buffer[0]) {
                        case '<':
                            result = atoi(op1) < atoi(op2);
                            break;
                        case '>':
                            result = atoi(op1) > atoi(op2);
                            break;
                        default:
                            result = atoi(op1) == atoi(op2);
                            break;
                    }
                    if (result == 0)
                        continue;
                    fscanf(fbas, "%[A-Z]", buffer);
                    type = command_type(buffer);
                    goto type_check;
                }

                //Определяем индексы переменных и регистрируем если требуется
                int id1 = var_id, id2 = var_id;
                if (isdigit(op1[0])) {
                    var[id1].name = tmp_var;
                    var[id1].address = 99 - var_id;
                    var[id1].init_value = atoi(op1);
                    ++var_id;
                    ++tmp_var;

                    id2 = variable_id(var, var_id, op2[0]);
                    if (id2 == var_id) {
                        var[id2].name = op2[0];
                        var[id2].address = 99 - var_id;
                        var[id2].init_value = 0;
                        ++var_id;
                    }
                } else if (isdigit(op2[0])) {
                    var[id2].name = tmp_var;
                    var[id2].address = 99 - var_id;
                    var[id2].init_value = atoi(op2);
                    ++var_id;
                    ++tmp_var;

                    id1 = variable_id(var, var_id, op1[0]);
                    if (id1 == var_id) {
                        var[id1].name = op1[0];
                        var[id1].address = 99 - var_id;
                        var[id1].init_value = 0;
                        ++var_id;
                    }
                } else {
                    id1 = variable_id(var, var_id, op1[0]);
                    if (id1 == var_id) {
                        var[id1].name = op1[0];
                        var[id1].address = 99 - var_id;
                        var[id1].init_value = 0;
                        ++var_id;
                    }

                    id2 = variable_id(var, var_id, op2[0]);
                    if (id2 == var_id) {
                        var[id2].name = op2[0];
                        var[id2].address = 99 - var_id;
                        var[id2].init_value = 0;
                        ++var_id;
                    }
                }

                switch (buffer[0]) {
                    case '<':
                        //Если при вычитание из 2 1го число отрицательное, значит оно больше
                        sprintf(buffer, "%02u LOAD %02u\n%02u SUB %02u\n%02u JNEG 00\n",
                                address, var[id2].address,
                                address + 1, var[id1].address,
                                address + 2);
                        address += 3;
                        _goto[goto_id].goto_line = line + 1;
                        _goto[goto_id].instratuction_address = strlen(asm_code) + 29;
                        ++goto_id;
                        break;
                    case '>':
                        //Если при вычитание из 1 2e число отрицательное, значит оно больше
                        sprintf(buffer, "%02u LOAD %02u\n%02u SUB %02u\n%02u JNEG 00\n",
                                address, var[id1].address,
                                address + 1, var[id2].address,
                                address + 2);
                        address += 3;
                        _goto[goto_id].goto_line = line + 1;
                        _goto[goto_id].instratuction_address = strlen(asm_code) + 29;
                        ++goto_id;
                        break;
                    default:
                        //Если при вычитание из 2 1го число 0 - равны
                        sprintf(buffer, "%02u LOAD %02u\n%02u SUB %02u\n%02u JZ %02u\n%02u JUMP 00\n",
                                address, var[id2].address,
                                address + 1, var[id1].address,
                                address + 2, address + 4,
                                address + 3);
                        address += 4;
                        _goto[goto_id].goto_line = line + 1;
                        _goto[goto_id].instratuction_address = strlen(asm_code) + 38;
                        ++goto_id;
                        break;
                }
                strcat(asm_code, buffer);
                fscanf(fbas, " %[A-Z] ", buffer);
                type = command_type(buffer);
                goto type_check;
            }
                break;
            case 6: {
                fscanf(fbas, "%[A-Z]", buffer);
                if (buffer[1] != 0 || !(buffer[0] >= 'A' && buffer[0] <= 'Z')) // переменная от A do Z 
                {
                    end = fail = 1;
                    break;
                }
                char toVar = buffer[0];
                char exp[256] = "\0";
                char rpn[256];
                fgets(exp, 255, fbas);
                translate_to_rpn(rpn, exp);
                if (strlen(rpn) > 1) {
                    char stack[100] = "\0";
                    int pos = 0;
                    for (size_t i = 0; rpn[i]; i++) {
                        if (pos > 1 && isalnum(rpn[i]) == 0) {

                            unsigned id;
                            char var1 = stack[pos - 2];
                            getVarID(id, var1);
                            sprintf(buffer, "%02u LOAD %02u\n", address, var[id].address);
                            strcat(asm_code, buffer);
                            ++address;

                            char var2 = stack[pos - 1];
                            getVarID(id, var2);
                            if (rpn[i] == '+')
                                sprintf(buffer, "%02u ADD %02u\n", address, var[id].address);
                            else if (rpn[i] == '-')
                                sprintf(buffer, "%02u SUB %02u\n", address, var[id].address);
                            else if (rpn[i] == '*')
                                sprintf(buffer, "%02u MUL %02u\n", address, var[id].address);
                            else if (rpn[i] == '/')
                                sprintf(buffer, "%02u DIV %02u\n", address, var[id].address);
                            strcat(asm_code, buffer);
                            ++address;

                            id = var_id;
                            var[id].name = tmp_var;
                            var[id].address = 99 - id;
                            var[id].init_value = 0;
                            ++tmp_var;
                            ++var_id;

                            sprintf(buffer, "%02u STORE %02u\n", address, var[id].address);
                            strcat(asm_code, buffer);
                            ++address;
                            pos--;
                            stack[pos - 1] = tmp_var - 1;
                        } else {
                            stack[pos] = rpn[i];
                            pos++;
                        }
                    }
                    sprintf(buffer, "%02u LOAD %02u\n", address, var[var_id - 1].address);
                    strcat(asm_code, buffer);
                    ++address;
                    int id;
                    getVarID(id, toVar);
                    sprintf(buffer, "%02u STORE %02u\n", address, var[id].address);
                    strcat(asm_code, buffer); // LOAD n STORE и отдельная ячейка памяти для вывода из аккума
                } else {
                    int id = var_id;
                    if (isdigit(rpn[0])) {
                        id = var_id;
                        ++var_id;
                        if (variable_id(var, var_id, toVar) == var_id) {
                            var[id].name = toVar;
                            var[id].address = 99 - id;
                            var[id].init_value = atoi(rpn);
                            --address;
                            break;
                        } else {
                            var[id].name = tmp_var;
                            var[id].address = 99 - id;
                            var[id].init_value = atoi(rpn);
                            ++tmp_var;
                        }
                    } else {
                        id = variable_id(var, var_id, rpn[0]);
                        if (id == var_id) {
                            var[id].name = rpn[0];
                            var[id].address = 99 - id;
                            var[id].init_value = 0;
                            ++var_id;
                        }
                    }

                    sprintf(buffer, "%02u LOAD %02u\n", address, var[id].address);
                    strcat(asm_code, buffer);
                    ++address;
                    id = variable_id(var, var_id, toVar);
                    if (id == var_id) {
                        var[id].name = toVar;
                        var[id].address = 99 - id;
                        var[id].init_value = 0;
                        ++var_id;
                    }
                    sprintf(buffer, "%02u STORE %02u\n", address, var[id].address);
                    strcat(asm_code, buffer);
                }
            }
                break;
            case 7:
                sprintf(buffer, "%02u HALT 00", address);
                strcat(asm_code, buffer);
                end = 1;
                break;
        }
        ++address;
        int ignore;
        do { ignore = fgetc(fbas); }
        while (ignore != '\n' && ignore != EOF);
        if (ignore == EOF)
            break;
    }

    //Запись в память начальных значений + констатнт
    //Проход по конфликтным переходам и заполнение их

    if (address + var_id > 99)
        fail = 1;

    if (fail == 0) {
        int id = 0;
        for (; id < goto_id; ++id) {
            int lid = 0;
            while (lid < line_id &&
                   lines[lid].line_number < _goto[id].goto_line)
                ++lid;
            if (lid != line_id) {
                sprintf(asm_code + _goto[id].instratuction_address, "%02u", lines[lid].start_address);
                asm_code[_goto[id].instratuction_address + 2] = '\n';
            }
        }

        for (id = var_id - 1; id >= 0; --id) {
            sprintf(buffer, "\n%02u = %x", var[id].address, var[id].init_value);
            strcat(asm_code, buffer);
        }

        FILE *fasm = fopen(filename_asm, "w");
        if (fasm != NULL) {
            fputs(asm_code, fasm);
            fclose(fasm);
        } else
            fail = 1;
    }

    free(buffer);
    free(_goto);
    free(var);
    free(lines);
    free(asm_code);
    return fail == 1;
}