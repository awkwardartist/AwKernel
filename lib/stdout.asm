global _flush_stdout
global _c_int

extern clear, sprint, UPDATE_CONSOLE, WRITE_C
_flush_stdout:
	mov edi, 0xb8000 ; dest=gbuffer
	mov ecx, 25*80   ; size of stdout
	; source=address just after 0xb8000
	mov esi, edi
	add esi, ecx
	inc esi ; pointing at 0x0

	rep movsb ; now move
	ret
_c_int: 
	cmp eax, 0
	je clear

	cmp eax, 1 ; sprint(ebx=char*)
	push ebx ; char*
	je sprint

	pop ebx
	cmp eax, 2
	; force update
	je UPDATE_CONSOLE
	
	cmp eax, 3
	; write char


