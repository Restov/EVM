#include "include/cu.h"

int Cu()
{
    int value = 0;
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
        sc_regSet(T, 0);
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
            mt_gotoXY(24, 15);
            //read_console(&value);
            printf("Enter: ");
            scanf("%X", &value);
            if (value > 0xFFFF)
            {
                sc_regSet(P, 1);
                break;
            }
            else
            {
                //rk_mytermregime(1, 0, 1, 1, 1);
                sc_memorySet(operand, value);
                mt_gotoXY(24, 15);
                break;
            }
        case WRITE:
            mt_gotoXY(24, 15);
            sc_memoryGet(operand, &value);
            printf("%ls\n", &value);
            mt_gotoXY(24, 15);
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