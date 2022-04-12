#pragma once
#include "types.h"
// defined in memory.asm:

// copy len amount of bytes from src to dest
extern void memcpy(void *dest, void *src, uint32_t len); 
extern int memcmp(void *b1, void *b2, uint32_t len);

// set memory to 0
extern void memclr(void*,uint32_t);

// get length of string
extern int strlen(char*);

// wait 1-4ms to give devices time
extern void io_wait();

// read data from io port
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);

// write data to io port
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
extern void outw(uint16_t port, uint16_t data);
