#include "include/myBigChars.h"
#include "include/myTerm.h"

int bc_printA (const char * str){
	printf(EN_MACS);
    if(printf("%s", str) < 0) {
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

	for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
		mt_gotoXY(x1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	bc_printA(BC_ANGLE_RIGHT_UP);

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1);
		bc_printA(BC_LINE_VERTICAL);
	}

	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA(BC_ANGLE_LEFT_DOWN);

	for (int i = x1 + 1; i <  x1 + x2 - 1; i++) {
		mt_gotoXY(i, y1 + y2 - 1);
		bc_printA(BC_LINE_VERTICAL);
	}

	for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
		mt_gotoXY(x1 + x2 - 1, i);
		bc_printA(BC_LINE_HORIZONTAL);
	}

	bc_printA(BC_ANGLE_RIGHT_DOWN);
	printf("\n");
	
	return 0;
}

int bc_printbigchar(int arr[2], int x, int y, enum colors b_col, enum colors f_col){
	return 0;
}