#include "efigdt.h"
static struct GDT_Entry gdt[3];
static struct GDT_Pointer gdt_ptr;

void setup_gdt(void) {
    gdt[0] = (struct GDT_Entry){0, 0, 0, 0, 0, 0};

    gdt[1] = (struct GDT_Entry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x9A,
        .granularity = 0xAF,
        .base_high = 0
    };
    gdt[2] = (struct GDT_Entry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x92,
        .granularity = 0xCF,
        .base_high = 0
    };
    gdt_ptr.limit = (sizeof(struct GDT_Entry) * 3) - 1;
    gdt_ptr.base = (UINT64)&gdt;
    asm volatile("lgdt %0" : : "m"(gdt_ptr));
}