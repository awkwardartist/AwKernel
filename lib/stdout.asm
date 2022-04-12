global _flush_stdout

_flush_stdout:
	mov edi, 0xb8000 ; dest=gbuffer
	mov ecx, 25*80   ; size of stdout
	; source=address just after 0xb8000
	mov esi, edi
	add esi, ecx
	inc esi ; pointing at 0x0

	rep movsb ; now move
	ret
