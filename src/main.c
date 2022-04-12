#include "memory.h"
#include "stdout.h" // a minimalistic console driver
#include "pic.h"

extern void kmain(void);
extern void gdt_install();
extern void idt_install();

void throw_irq() {
	return;
}

extern void CONSOLE_INT(void);
void kmain() {
	// clear console and print
	clear();
	sprint("running kernel awkernel-proto-0.0.1\n\n");
	
	sprint("get base processes working:\n");
	info("initializing GDT and IDT...");
	// initialize gdt & idt
	gdt_install();
	success("initialized GDT");
    idt_install();
	success("initialized IDT");
	
	info("initializing PIC (0x90-0x97)");
	pic_remap(0x90, 0x97);
	success("initialized PIC");
	
	info("set all standard irq masks");
	for(int i = 0; i < 16; i++)
		irq_set_mask(i);
	success("set, now enable interrupts");
	asm("sti");
	success("interrupts enabled");
	
	IDENTIFY(1);
	success("done");
	while(1);
}
