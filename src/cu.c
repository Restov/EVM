#include "cu.h"

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
    if (command >= 0x30 && command <= 0x33)
    {
        Alu(command, operand);
        return 1;
    }
    else
    {
        switch (command)
        {
        case READ:
            mt_gotoXY(24, 15);
            printf("Enter value: ");
            scanf("%d", &value);
            sc_memorySet(operand, value);
            mt_gotoXY(24, 15);
            break;
        case WRITE:
            mt_gotoXY(24, 15);
            sc_memoryGet(operand, value);
            printf("%d\n", &value);
            mt_gotoXY(24, 15);
            break;
        case LOAD:
            sc_memoryGet(operand, &accumulator); // узнать тут инкаунтер или опперанд
            break;
        case STORE:
            sc_memorySet(operand, &accumulator); // и тут тоже
            break;
        case JUMP:
            if (operand >= SIZE || operand < 0)
            {
                sc_regSet(M, 1);
                break;
            }
            instructionCounter = operand;
            break;
        case JNEG:
            if (accumulator < 0)
            {
                if (operand >= SIZE || operand < 0)
                {
                    sc_regSet(M, 1);
                    break;
                }
                instructionCounter = operand;
            }
            break;
        case JZ:
            if (accumulator == 0)
            {
                if (operand >= SIZE || operand < 0)
                {
                    sc_regSet(M, 1);
                    break;
                }
                instructionCounter = operand;
            }
            break;
        case HALT:
            sc_regSet(T, 0);
            return 1;
            break;
        case JNP:
            if ((accumulator % 2) != 0)
            {
                if (operand >= SIZE || operand < 0)
                {
                    sc_regSet(M, 1);
                    break;
                }
                instructionCounter = operand;
            }
            break;
        }
    }
    return 0;
}

int Alu(int command, int operand)
{
    int value = 0;
    sc_memoryGet(instructionCounter, &value);
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
}