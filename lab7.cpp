#include "mbr.h"

int get_headers(int head, int max_head) {
    int i = 1, max = 0;
    do {
        if (head & i)
            max = i;
    } while ((i <<= 1) < max_head);
    max *= 2;
    return (!max ? 2 : (max > max_head ? max_head : max));
}

int a_lba2chs (tCHS geometry, tLBA lba, tCHS *chs) {
    if (((uint32_t)(geometry.sector) * geometry.head * geometry.cylinder) < lba) {
        chs->sector = geometry.sector;
        chs->head = geometry.head;
        chs->cylinder = geometry.cylinder;
    } else {
        chs->sector = lba % geometry.sector + 1;
        chs->head = (lba / geometry.sector) % geometry.head;
        chs->cylinder = lba / (geometry.head * geometry.sector);
    }
    return 0;
}

int a_lba2large (tLARGE geometry, tLBA lba, tLARGE *large) {
    if (((uint32_t)(geometry.sector) * geometry.head * geometry.cylinder) < lba) {
        large->sector = geometry.sector;
        large->head = geometry.head;
        large->cylinder = geometry.cylinder;
    } else {
        large->sector = lba % geometry.sector + 1;
        large->head = (lba / geometry.sector) % geometry.head;
        large->cylinder = lba / (geometry.head * geometry.sector);
    }
    return 0;
}

int a_lba2idechs (tIDECHS geometry, tLBA lba, tIDECHS *ide) {
    if (((uint32_t)(geometry.sector) * geometry.head * geometry.cylinder) < lba) {
        ide->sector = geometry.sector;
        ide->head = geometry.head;
        ide->cylinder = geometry.cylinder;
    } else {
        ide->sector = lba % geometry.sector + 1;
        ide->head = (lba / geometry.sector) % geometry.head;
        ide->cylinder = lba / (geometry.head * geometry.sector);
    }
    return 0;
}

int a_chs2lba (tCHS geometry, tCHS chs, tLBA *lba) {
    *lba = (chs.cylinder * geometry.head + chs.head) * geometry.sector + chs.sector - 1;
    return 0;
}

int a_large2lba (tLARGE geometry, tLARGE large, tLBA *lba) {
    *lba = (large.cylinder * geometry.head + large.head) * geometry.sector + large.sector - 1;
    return 0;
}

int a_idechs2lba (tIDECHS geometry, tIDECHS ide, tLBA *lba) {
    *lba = (ide.cylinder * geometry.head + ide.head) * geometry.sector + ide.sector - 1;
    return 0;
}

int a_large2chs (tLARGE geometry1, tCHS geometry2, tLARGE large, tCHS *chs) {
    int coeff = geometry1.head / geometry2.head;
    if (coeff % 2)
        coeff += 1;
    while (large.head % coeff)
        if (coeff > large.head)
            return 1;
        else
            coeff += 2;
    if (large.cylinder * coeff > geometry2.cylinder ||
            large.head / coeff > geometry2.head)
        return 1;
    chs->sector = large.sector;
    chs->head = large.head / coeff;
    chs->cylinder = large.cylinder * coeff;
}

int a_large2idechs (tLARGE geometry1, tIDECHS geometry2, tLARGE large, tIDECHS *ide) {
    int coeff = geometry1.head / geometry2.head;
    if (coeff % 2)
        coeff += 1;
    while (large.head % coeff)
        if (coeff > large.head)
            return 1;
        else
            coeff += 2;
    if (large.cylinder * coeff > geometry2.cylinder ||
        large.head / coeff > geometry2.head)
        return 1;
    ide->sector = large.sector;
    ide->head = large.head / coeff;
    ide->cylinder = large.cylinder * coeff;
}

int a_chs2large (tCHS geometry1, tLARGE geometry2, tCHS chs, tLARGE *large) {
    int coeff = geometry2.head / geometry1.head;
    if (coeff % 2)
        coeff += 1;
    while (chs.cylinder % coeff)
        if (coeff > chs.cylinder ||
            coeff > geometry1.cylinder)
            return 1;
        else
            coeff += 2;
    if (chs.cylinder / coeff > geometry2.cylinder ||
            chs.head * coeff > geometry2.head)
        return 1;
    large->sector = chs.sector;
    large->head = chs.head * coeff;
    large->cylinder = chs.cylinder / coeff;
}

int a_idechs2large (tIDECHS geometry1, tLARGE geometry2, tIDECHS ide, tLARGE *large) {
    int coeff = geometry2.head / geometry1.head;
    if (coeff % 2)
        coeff += 1;
    while (ide.cylinder % coeff)
        if (coeff > ide.cylinder ||
            coeff > geometry1.cylinder)
            return 1;
        else
            coeff += 2;
    if (ide.cylinder / coeff > geometry2.cylinder ||
            ide.head * coeff > geometry2.head)
        return 1;
    large->sector = ide.sector;
    large->head = ide.head * coeff;
    large->cylinder = ide.cylinder / coeff;
}

int a_chs2idechs (tCHS geometry1, tIDECHS geometry2, tCHS chs, tIDECHS *ide) {
    if (chs.head > geometry2.head || chs.cylinder > geometry2.cylinder ||
            chs.sector > geometry2.sector)
        return 1;
    ide->head = chs.head;
    ide->cylinder = chs.cylinder;
    ide->sector = chs.sector;
}

int a_idechs2chs (tIDECHS geometry1, tCHS geometry2, tIDECHS ide, tCHS *chs) {
    if (ide.head > geometry2.head || ide.cylinder > geometry2.cylinder ||
            ide.sector > geometry2.sector)
        return 1;
    chs->head = ide.head;
    chs->cylinder = ide.cylinder;
    chs->sector = ide.sector;
}

int g_lba2chs(tLBA lba, tCHS *chs) {
    const unsigned sectors = 31;
    const unsigned heads = 16;
    uint16_t sector = lba % sectors + 1,
             head = (lba / sectors) % heads,
             cylinder = lba / (heads * sectors);
    if (sector > sectors || head > heads || cylinder > 1023) {
        chs->sector = sectors;
        chs->head = heads;
        chs->cylinder = 1023;
    } else {
        chs->sector = sector;
        chs->head = head;
        chs->cylinder = cylinder;
    }
    return 0;
}

int g_lba2large(tLBA lba, tLARGE *large) {
    //const unsigned cylinders = 1023;
    const unsigned sectors = 31;
    const unsigned heads = 255;//get_headers(lba / (sectors * cylinders), 255);
    uint16_t sector = lba % sectors + 1,
             head = (lba / sectors) % heads,
             cylinder = lba / (heads * sectors);
    if (sector > sectors || head > heads || cylinder > 1023) {
        large->sector = sectors;
        large->head = heads;
        large->cylinder = 1023;
    } else {
        large->sector = sector;
        large->head = head;
        large->cylinder = cylinder;
    }
    return 0;
}

int g_lba2idechs(tLBA lba, tIDECHS *ide) {
    const unsigned sectors = 255;
    const unsigned heads = 16;
    uint16_t sector = lba % sectors + 1,
             head = (lba / sectors) % heads,
             cylinder = lba / (heads * sectors);
    if (sector > sectors || head > heads || cylinder > 0xFFFF) {
        ide->sector = sectors;
        ide->head = heads;
        ide->cylinder = 0xFFFF;
    } else {
        ide->sector = sector;
        ide->head = head;
        ide->cylinder = cylinder;
    }
    return 0;
}

int g_chs2lba(tCHS chs, tLBA *lba) {
    *lba = chs.cylinder * chs.head * chs.sector;
    return 0;
}

int g_chs2large(tCHS chs, tLARGE *large) {
    large->sector = chs.sector;
    uint8_t coeff = 1;
    /*if (chs.head)
    while (!(chs.cylinder % coeff) &&
            (chs.cylinder / coeff) > 0 &&
            coeff * chs.head * 2 < 256)
        coeff <<= 1;*/
    if (!((chs.cylinder + 1) % 2))
        coeff = 2;
    large->cylinder = chs.cylinder / coeff;
    large->head = chs.head * coeff;
    return 0;
}

int g_chs2idechs(tCHS chs, tIDECHS *ide) {
    ide->head = chs.head;
    ide->sector = chs.sector;
    ide->cylinder = chs.cylinder;
    return 0;
}

int g_large2lba(tLARGE large, tLBA *lba) {
    *lba = large.cylinder  * large.head * large.sector;
    return 0;
}

int g_large2chs(tLARGE large, tCHS *chs) {
    chs->sector = large.sector;
    uint8_t coeff = 1;
    if ((large.cylinder + 1) < 512 && !((large.head + 1) % 2))
        coeff = 2;
    chs->cylinder = (large.cylinder + 1) * coeff - 1;
    chs->head = (large.head + 1) / coeff;
    return 0;
}

int g_large2idechs(tLARGE large, tIDECHS *ide) {
    ide->sector = large.sector;
    uint8_t coeff = 16;
    for (; coeff > 0 && (large.head + 1) % coeff;)
        coeff >>= 1;
    ide->cylinder = (large.cylinder + 1) * coeff - 1;
    ide->head = (large.head + 1) / coeff - 1;
    return 0;
}

int g_idechs2lba(tIDECHS ide, tLBA *lba) {
    *lba = ide.cylinder * ide.head * ide.sector;
    return 0;
}

int g_idechs2chs(tIDECHS ide, tCHS *chs) {
    tLBA lba;
    g_idechs2lba(ide, &lba);
    return g_lba2chs(lba, chs);
}

int g_idechs2ilarge(tIDECHS ide, tLARGE *large) {
    tLBA lba;
    g_idechs2lba(ide, &lba);
    return g_lba2large(lba, large);
}
