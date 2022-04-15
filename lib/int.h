#pragma once
#include "types.h"

extern void gdt_install(void);
extern void idt_install(void);
extern void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
extern void idt_add_intr(uint8_t num, uint32_t base);
