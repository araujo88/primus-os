global time

section .text
time:
	push ebp
	mov ebp, esp
    datetime dw __TIME__, 0x0
	mov eax, datetime
	mov esp, ebp
	pop ebp
	ret