#include "types.h"
#include "memory.h"

// for readability
enum {
	PRIMARY,
	SECONDARY
};

struct _driveinfo {
	// compatability for lba28/48/chs
	uint8_t lba48, lba28, chs;
	uint16_t *RAW;
};

// holds the primary and secondary io ports
// for control/cmd base
uint16_t bus_cmd[2] = { 0x1F0, 0x170 };
uint16_t bus_ctl[2] = { 0x3F6, 0x376 };

// 0 = primary, 1 = secondary
int selected_bus=0;

int IS_FREE() {
	uint8_t stat = inb(bus_ctl[selected_bus]+0); // stat=ctl_base+0
	if(stat & (1<<7)) 
		return 0;
	else if(stat & 1)
		return 0;
	else if(!(stat & (1<<6)))
		return 0;
	
	return 1;
}
void DELAY() {
	for(int i = 0; i < 14; i++)
		inb(bus_ctl[selected_bus]);
	return inb(bus_ctl[selected_bus]);
}

void DRIVE_SELECT(uint8_t primary) {
	// resolve drive id
	uint8_t drive_id;
	if(primary) drive_id = 0xA0;
	else drive_id = 0xB0;
	
	// output to drive select io port for selected bus
	// (io_base+6) = drive register
	outb(bus_cmd[selected_bus]+6, drive_id); 
	
	//while(!IS_FREE()) {io_wait();} // wait for drive to be free
	
}
void WAIT_FREE() {
	while(!IS_FREE());
}
struct _driveinfo *IDENTIFY(uint8_t primary) {
	DRIVE_SELECT(primary);
	for(int i = 2; i < 7; i++) {
		outb(bus_cmd[selected_bus]+i, 0x0); // set to 0
	}
	
}
