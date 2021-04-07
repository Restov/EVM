#include "cu.h"

int Cu()
{
    int value = 0;
    sc_memoryGet(instructionCounter, &value);
    int command;
    int operand;
    sc_commandDecode(value, command, operand);
    if (command >= 0x30 && command <= 0x33)
    {
        Alu(command, operand);
        return 1;
    }
    switch (command)
    {
    case READ:
        mt_gotoXY(24, 15);
		scanf("%d", &value);
		sc_memorySet(instructionCounter, value);
        mt_gotoXY(24, 15);
        break;
    case WRITE:
        mt_gotoXY(24, 15);
        sc_memoryGet(instructionCounter, value);
		printf("%d\n", &value);
		mt_gotoXY(24, 15);
        break;
    case LOAD:
        sc_memoryGet(instructionCounter, &accumulator); // узнать тут инкаунтер или опперанд
        break;
    case STORE:
        sc_memorySet(instructionCounter, &accumulator); // и тут тоже
        break;
    case JUMP:
        
        break;
    case JNEG:
        break;
    case JZ:

        break;
    case HALT:
        sc_regSet(T, 1);
        return 1;
        break;
    default:
        sc_regSet(T, 1);
        break;
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