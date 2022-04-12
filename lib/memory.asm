global memcpy ; make available to C code
global memcpy_r
global memcmp
global memclr
global strlen
global outb
global outw
global outl
global inb
global inw
global inl
global io_wait

io_wait:
	; send 0x0 to 0x80
	xor al, al
	out 0x80, al
	ret

memclr: ; void memclr(void *buff, uint32_t len)
	pop edx   ; pop address
	pop eax   ; buff
	pop ecx   ; len
memclr_loop:
	mov byte [eax], 0
	inc eax     ; move to next byte

	loop memclr_loop
	
	push edx   ; push address
	ret        ; return to kernel

memcpy_r: ; reverse memcpy (copy in reverse)
	std ; set direction flag
memcpy: ; void memcpy(void *dest, void *src, uint32_t len)
	pop eax ; store return address

	; get arguments
	pop edi   ; pop dest* to dest reg
	pop esi   ; pop src* to src reg
	pop ecx   ; pop ecx (# of bytes)
	
	rep movsb ; transfer bytes
	push eax  ; restore return address
	
	cld       ; make sure direction flag is clear
	ret       ; return to kernel

outb: ; void outb(uint16_t port, uint8_t data)
	pop ebx ; store ret addr
	pop edx ; (dx) port
	pop eax ; (al) data

	out dx, al
	push ebx
	ret
outw:
	pop ebx
	pop edx
	pop eax

	out dx, ax
	push ebx
	ret
outl:
	pop ebx
	pop edx
	pop eax
	
	out dx, eax
	push ebx
	ret

inb: ; uint8_t inb(uint16_t port)
	pop ebx ; store ret addr
	pop edx ; (dx) port

	xor eax, eax ; free eax
	in al, dx ; store result in al

	push eax
	push ebx
	ret

inw:
	pop ebx ; store ret addr
	pop edx ; (dx) port

	xor eax, eax ; free eax
	in ax, dx ; store result in ax

	push eax
	push ebx
	ret
inl:
	pop ebx
	pop edx

	xor eax, eax
	in eax, dx

	push eax
	push ebx
	ret
memcmp: ; int memcmp(void *b1, void *b2, uint32_t len)
	pop edx ; store ret address

	; get args:
	pop eax ; b1
	pop ebx ; b2
	pop ecx ; len
	
	push edx ; edx will be destroyed, so save
memcmp_loop:
	; store bytes
	mov dl, byte [eax]
	mov dh, byte [ebx]

	cmp dl, dh         ; compare
	jne memcmp_fail    ; if inequal, return false
	
	; increment for next compare
	inc eax
	inc ebx

	loop memcmp_loop   ; loop until ecx = 0

	mov eax, 1         ; ret code = 1
	jmp memcmp_end     ; loop ended, so terminate
memcmp_fail:
	xor eax, eax       ; clear return code
memcmp_end:
	pop edx            ; pop address (it needs to go after ret val)
	push eax           ; push return value
	push edx           ; push address
	ret                ; return to kernel

strlen: ; int strlen(char* str)
	pop edx ; ret addr
	pop eax ; str

	xor ebx, ebx ; free ebx
strlen_loop:
	cmp byte [eax], 0
	je strlen_end

	inc eax
	inc ebx
	jmp strlen_loop
strlen_end:
	push ebx ; return len
	push edx ; push ret addr
	ret
