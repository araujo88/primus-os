global date

section .text
date:
	push ebp
	mov ebp, esp
	datetime db __DATE__, 0x0
	mov eax, datetime
	mov esp, ebp
	pop ebp
	ret