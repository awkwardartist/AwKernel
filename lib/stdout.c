#include "memory.h"
#include "types.h"

#define BUFFER 0xb8000
#define DBUFFER (0xb8000+(80*25)*2)

extern void SCROLL();
enum {
	BLACK, BLUE, GREEN,
	CYAN, RED, MAGENTA,
	BROWN, LGRAY, DGRAY,
	LBLUE, LGREEN, LCYAN,
	LRED, LMAGENTA, YELLOW,
	WHITE
};

int init=0;

uint32_t x=0, y=0; // cursor coordinates

uint32_t console_width=80;
uint32_t console_height=25;

char *GET_CURRENT() {
	char *b = (char*)DBUFFER; // get terminal buffer

	int offset = (y * (console_width)) + x; // calculate offset
	return &(b[offset*2]); // return buffer using offset
}
char *GET_LOC(uint32_t X, uint32_t Y) {
	uint32_t x_bak = x, y_bak = y; // store x and y
	x = X; y = Y; // assign
	
	char *ret = GET_CURRENT(); // get ret
	x = x_bak; y = y_bak; // restore
	return ret;
}
// copies the secondary buffer to the actual graphics buffer
void UPDATE_CONSOLE() {
	memcpy((void*)BUFFER, (void*)DBUFFER, (80*25)*2); // copy memory
}

void RECALC_POS() {
	// auto newline
	if(x >= console_width) {
		// move to next row
		x -= console_width;
		if(x < 0) x = 0;
		y++;
	}

	// auto scroll
	if(y >= console_height-1) {
		SCROLL();
	}

}

// writes a single character to the
// secondary buffer
void WRITE_C(char c) {
	// special characters:
	switch(c) {
		case '\n':
			x = 0;
			y++;
			return; // end
		case '\t':
			while(++x % 4); // increment until multiple of 4
			RECALC_POS();
			return;
	}

	RECALC_POS(); // make sure no errors occur
	char *b = GET_CURRENT(); // get current address
	
	*b = c; // assign character
	*(b+1) = 0x7; // assign white color
	x++; // move up one
}

void sprint(char *s) {
	for(int i=0; s[i]; i++) {
		WRITE_C(s[i]);
	}
	UPDATE_CONSOLE(); // write changes
}

void colprint(char *s, unsigned char col) {
	for(int i = 0; s[i]; i++) {
		WRITE_C(s[i]); // print to stdout
		*(GET_CURRENT() - 1) = col; // set col
	}
	UPDATE_CONSOLE();
}
void set_cursor(int X, int Y) {
	x = X;
	y = Y;
}
void offset_cursor(int X, int Y) {
	x += X;
	y += Y;
}
void success(char* s) {
	sprint("[");
	colprint(" success ", GREEN);
	sprint("] ");
	sprint(s);
	WRITE_C('\n');
}
void info(char *s) {
	sprint("[");
	colprint(" message ", MAGENTA);
	sprint("] ");
	sprint(s);
	WRITE_C('\n');
}
void error(char *s) {
	sprint("[");
	colprint(" error ", RED);
	sprint("] ");
	sprint(s);
}

void clear() {
	memclr((void*)DBUFFER, 80*25*2); // fill with 0x0
	memclr((void*)BUFFER, 80*25*2); // also clear
}

// scroll up one character
void SCROLL() {
	for(int _y = 1; _y < console_height; _y++) {
		char *src = GET_LOC(0, _y); // get position of layer
		char *dst = GET_LOC(0, _y-1); // get last layer
		memcpy((void*)dst, (void*)src, console_width*2); // copy up one
	}
	char nullchr[console_width];
	memcpy((void*)GET_LOC(0, console_height), (void*)nullchr, console_width);
	UPDATE_CONSOLE();
	y--;
}

