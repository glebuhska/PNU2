#ifndef EFIGDT_H
#define EFIGDT_H

#include "efi.h" 
struct GDT_Entry {
    UINT16 limit_low;
    UINT16 base_low;
    UINT8  base_middle;
    UINT8  access;
    UINT8  granularity;
    UINT8  base_high;
} __attribute__((packed));

struct GDT_Pointer {
    UINT16 limit;
    UINT64 base;
} __attribute__((packed));

void setup_gdt(void);

#endif