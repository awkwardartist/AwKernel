; the entry application
bits    32 ;protected mode


section .text
    align 4
    dd 0x1BADB002
    dd 0
    dd - (0x1BADB002+0)
global start
extern kmain
start:
    call kmain
    hlt