#ifndef DISK_H
#define DISK_H

#include <inttypes.h>

typedef struct {
    uint16_t sector : 6;
    uint16_t cylinder : 10;
    uint8_t head : 4;
} tCHS;//20 bit

typedef struct {
    uint16_t sector : 6;
    uint16_t cylinder : 10;
    uint8_t head;
} tLARGE;//24 bit

typedef struct {
    uint32_t head : 4;
    uint32_t sector : 8;
    uint32_t cylinder : 16;
} tIDECHS;//28 bit

typedef uint32_t tLBA;//32 bit

int get_headers(int head, int max_head);
int a_lba2chs (tCHS geometry, tLBA lba, tCHS *chs);
int a_lba2large (tLARGE geometry, tLBA lba, tLARGE *large);
int a_lba2idechs (tIDECHS geometry, tLBA lba, tIDECHS *ide);
int a_chs2lba (tCHS geometry, tCHS chs, tLBA *lba);
int a_large2lba (tLARGE geometry, tLARGE large, tLBA *lba);
int a_idechs2lba (tIDECHS geometry, tIDECHS ide, tLBA *lba);
int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE large, tCHS *chs);
int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE large, tIDECHS *ide);
int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS chs, tLARGE *large);
int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS ide, tLARGE *large);
int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS chs, tIDECHS *ide);
int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS ide, tCHS *chs);
int g_lba2chs(tLBA lba, tCHS *chs);
int g_lba2large(tLBA lba, tLARGE *large);
int g_lba2idechs(tLBA lba, tIDECHS *ide);
int g_chs2lba(tCHS chs, tLBA *lba);
int g_chs2large(tCHS chs, tLARGE *large);
int g_chs2idechs(tCHS chs, tIDECHS *ide);
int g_large2lba(tLARGE large, tLBA *lba);
int g_large2chs(tLARGE large, tCHS *chs);
int g_large2idechs(tLARGE large, tIDECHS *ide);
int g_idechs2lba(tIDECHS ide, tLBA *lba);
int g_idechs2chs(tIDECHS ide, tCHS *chs);
int g_idechs2ilarge(tIDECHS ide, tLARGE *large);
#endif //DISK_H