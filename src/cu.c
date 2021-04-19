#include "include/cu.h"

int Cu()
{
    int value = 0;
    int temp = 0;
    sc_memoryGet(instructionCounter, &value);
    int command;
    int operand;
    if (sc_commandDecode(value, &command, &operand))
    {
        sc_regSet(T, 0);
        return 1;
    }
    if (operand >= SIZE || operand < 0)
    {
        sc_regSet(M, 1);
        sc_regSet(T, 1);
        return 1;
    }
    if (command >= 0x30 && command <= 0x33)
    {
        Alu(command, operand);
    }
    else
    {
        switch (command)
        {
        case READ:
            rk_mytermregime(1, 0, 1, 0, 0);
            read_console_value(operand, &value);
            rk_mytermregime(1, 0, 1, 1, 0);
            if (value > 0xFFFF)
            {
                sc_regSet(P, 1);
                break;
            }
            else
            {
                sc_memorySet(operand, value);
                mt_gotoXY(24, 1);
                break;
            }
        case WRITE:
            temp = write_console_value(operand, value);
            mt_gotoXY(25, 1);
            printf("Address = %d, value = %d\n", operand, temp);
            sleep(5);
            break;
        case LOAD:
            sc_memoryGet(operand, &accumulator);
            break;
        case STORE:
            sc_memorySet(operand, accumulator);
            break;
        case JUMP:
            instructionCounter = --operand;
            break;
        case JNEG:
            if (accumulator < 0)
            {
                instructionCounter = --operand;
            }
            break;
        case JNS:
            if (accumulator > 0)
            {
                instructionCounter = --operand;
            }
            break;
        case JZ:
            if (accumulator == 0)
            {
                instructionCounter = --operand;
            }
            break;
        case HALT:
            sc_regSet(T, 1);
            return 0;
            break;
        case NOT:
            value = ~accumulator;
            sc_memorySet(operand, value);
            break;
        case JNP:
            if ((accumulator % 2) != 0)
            {
                instructionCounter = --operand;
            }
            break;
        }
    }
    if (instructionCounter + 1 < SIZE)
    {
        instructionCounter++;
        coord = instructionCounter;
    }
    else
    {
        sc_regSet(M, 1);
    }

    return 0;
}

int Alu(int command, int operand)
{
    int value = 0;
    sc_memoryGet(operand, &value);
    switch (command)
    {
    case ADD:
        if (accumulator + value > 0xFFFF)
        {
            sc_regSet(P, 1);
            break;
        }
        accumulator += value;
        break;
    case SUB:
        if (accumulator - value < -0xFFFF)
        {
            sc_regSet(P, 1);
            break;
        }
        accumulator -= value;
        break;
    case DIVIDE:
        if (accumulator == 0)
        {
            sc_regSet(O, 1);
            break;
        }
        accumulator /= value;
        break;
    case MUL:
        if (accumulator * value > 0xFFFF)
        {
            sc_regSet(P, 1);
            break;
        }
        accumulator *= value;
        break;
    default:
        sc_regSet(E, 1);
        break;
    }
    return 0;
}