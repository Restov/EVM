#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "include/disk.h"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define CYAN  "\033[1;36m"
#define YELLOW "\033[1;33m"
void table_types(void);

int main() {
    
    int C, H, S, sizeS, type, sum_t = 0, active, total_types[9] = {0},  flag = 0;
    double MaxSize, UseSize = 0, s;
    double BaseTable[9][10] = {0};
    tCHS    chs, geometry; 
//    tLARGE  large;
//    tIDECHS ide;
    tLBA    lba;

    printf("Input CHS:\n");
    printf("[C] cylinder: "); scanf("%d", &C);
    printf("[H] heads: ");    scanf("%d", &H);
    H = get_headers(H, 16);
    printf("[S] sector: ");   scanf("%d", &S);
    printf("Sizeof sector (byte): ");
    scanf("%d", &sizeS);
    printf("\n%sMax size of Hard disk:%s", YELLOW, RESET);
    MaxSize = H * C * S * sizeS;
    printf("\n%d*%d*%d*%d"
           " = %s%f Gb%s\n", H, C, S, sizeS, GREEN, MaxSize /= (1024.0*1024*1024), RESET);
    geometry.sector = S; geometry.cylinder = C; geometry.head = H;
    
    while (UseSize < MaxSize) {
        printf("\n%sInput need size(Gb)(%f left): %s", YELLOW, MaxSize - UseSize,  RESET);
        scanf("%lf", &s);
        if (!s || s > MaxSize) break;
        
        table_types();
        scanf("%d", &type);
        if (type > 0 && type < 10) {
            if (total_types[type-1] == 0) {
                if (sum_t == 0) BaseTable[type-1][8] = 1;                
                total_types[type-1] = sum_t + 1;
                sum_t++;
                BaseTable[type-1][9] = s;           
            } else {
                BaseTable[type-1][9] += s;
            }
            BaseTable[type-1][4] = type;
            UseSize += s;
        } else return -1;
                
        printf("%sIt is active ?(1/0): %s", YELLOW, RESET);
        scanf("%d", &active);
        if ((active == 1) && (flag == 1)) { printf("INCORRECT!\n"); active = 0;}
        else if ((active == 1) && (flag == 0)) flag=1;
        BaseTable[type-1][0] = active;
    }
    
    for(int j = 0; j < 9; ++j)
    if (total_types[j] == 1) {
        lba = BaseTable[j][9]*1024*1024*1024+1;
        a_lba2chs(geometry, lba, &chs);
        BaseTable[j][5] = chs.cylinder;
        BaseTable[j][6] = chs.head;
        BaseTable[j][7] = chs.sector;
        BaseTable[j][1] = 0;
        BaseTable[j][2] = 2;
        BaseTable[j][3] = 0;
    }
            
    for(int i = 2; i <= sum_t; ++i) {
        for(int j = 0; j < 9; ++j)
            if (total_types[j] == i) {
                BaseTable[j][8] = lba;
                a_lba2chs(geometry, lba, &chs);
                BaseTable[j][1] = chs.cylinder;
                BaseTable[j][2] = chs.head;
                BaseTable[j][3] = chs.sector;
                
                lba = BaseTable[j][8] + BaseTable[j][9]*1024*1024*1024;
                a_lba2chs(geometry, lba, &chs);
                BaseTable[j][5] = chs.cylinder;
                BaseTable[j][6] = chs.head;
                BaseTable[j][7] = chs.sector;
                
            }
     }


    printf("A| CHS  start|S| CHS   end |LBAs|Size |\n");
    for(int i = 1; i <= sum_t; ++i) {
        for(int j = 0; j < 9; ++j)
            if (total_types[j] == i) {
                printf("%.0f|%3.0f|%3.0f|%3.0f|%.0f|%3.0f|%3.0f|%3.0f|%10.0f|%.3f|\n",
                BaseTable[j][0], BaseTable[j][1], BaseTable[j][2],
                BaseTable[j][3], BaseTable[j][4], BaseTable[j][5],
                BaseTable[j][6], BaseTable[j][7], BaseTable[j][8],
                BaseTable[j][9]);
            }
    }
    return 0;
}

void table_types() {
    printf("\n%sInput number of the types that you need (exit 0) %s\n", YELLOW, RESET);
    printf("1)Empty(00)\n2)FAT12(01)\n3)FAT16(04)\n"
           "4)EXTENDED(05)\n5)MS-DOS FAT16(06)\n6)HPFS/NTFS(07)\n"
           "7)Win95 FAT32 LBA(0E)\n8)Linux swap(82)\n9)Linux(83)\n:");
}

