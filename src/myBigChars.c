#include "include/myBigChars.h"
#include "include/myTerm.h"

int bc_printA(const char *str)
{
	printf(EN_MACS);
	if (printf("%s", str) < 0)
	{
		return -1;
	}
	printf(EX_MACS);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || y1 < 0)
		return -1;

	mt_gotoXY(x1, y1);
	bc_printA(BC_ANGLE_LEFT_UP);

	for (int i = y1 + 1; i < y1 + y2 - 1; i++)
	{
		mt_gotoXY(x1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	bc_printA(BC_ANGLE_RIGHT_UP);

	for (int i = x1 + 1; i < x1 + x2 - 1; i++)
	{
		mt_gotoXY(i, y1);
		bc_printA(BC_LINE_VERTICAL);
	}

	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA(BC_ANGLE_LEFT_DOWN);

	for (int i = x1 + 1; i < x1 + x2 - 1; i++)
	{
		mt_gotoXY(i, y1 + y2 - 1);
		bc_printA(BC_LINE_VERTICAL);
	}

	for (int i = y1 + 1; i < y1 + y2 - 1; i++)
	{
		mt_gotoXY(x1 + x2 - 1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	bc_printA(BC_ANGLE_RIGHT_DOWN);
	printf("\n");

	return 0;
}

int bc_printbigchar(int arr[2], int x, int y, enum colors b_col, enum colors f_col)
{
	int w_x, w_y;
	mt_getscreensize(&w_x, &w_y);
	if (x < 0 || y < 0 || x > w_x || y > w_y)
		return -1;

	char str[8] = {0};
	mt_setfgcolor(f_col);
	mt_setbgcolor(b_col);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int a_buf = arr[i] >> (j * 8);
			int buf = a_buf & 255;
			for (int k = 0; k < 8; k++)
			{
				int buf_bit = (buf & (1 << k));
				if (buf_bit != 0)
				{
					str[k] = BLACK_CHAR;
				}
				else
				{
					str[k] = ' ';
				}
			}
			mt_gotoXY(x + (i * 4) + j + 1, y);
			bc_printA(str);
		}
	}
	mt_defcolor();
	mt_gotoXY(24, 0);
	return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value)
{
	if (x < 0 || y < 0 || x > 7 || y > 7 || value > 1 || value < 0)
		return -1;

	int index = 0;
	if (x > 3)
		index = 1;

	if (value == 1)
	{
		big[index] |= 1 << (x * 8 + y);
	}
	else if (value == 0)
	{
		big[index] &= ~(1 << (x * 8 + y));
	}
	return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return -1;

	int ind = 0;
	if (x > 3)
		ind = 1;

	*value = ((big[ind] >> (x * 8)) >> y) & 1;

	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
	if (big < 0 || fd < 0 || count < 0)
		return -1;

	if (write(fd, big, count * 8) == -1)
		return -1;
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	if (fd < 0 || need_count < 0)
	{
		*count = 0;
		return -1;
	}

	int result = read(fd, big, need_count * 8);
	if (result == -1)
	{
		*count = 0;
		return -1;
	}

	*count = result / 8;
	return 0;
}