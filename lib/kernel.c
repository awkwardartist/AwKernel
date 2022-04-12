#include "types.h"
#define SYSCALL_RES 8

uint32_t *syscalls;
int syscalls_i=SYSCALL_RES;
void SYSCALL() {
	register uint32_t id asm("eax"); // get value of eax
	

	while(1);
}

void add_syscall(uint32_t func, int syscall_id) {
	syscalls[syscalls_i++] = func;
}
