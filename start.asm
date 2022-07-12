bits 32
global _start
extern kernel_early
extern main

section .text
	align 4					; enforce alignment of instruction
	dd 0x1BADB002			; magic number (double-word) required by GRUB
	dd 0x00					; flags
	dd - (0x1BAD002 + 0x00)	; checksum

_start:
	cli						; clear interrupts
	mov esp, stack			; point the stack pointer to allocate memory
	call kernel_early		; function to be called before main
	call main				; call external main function
	hlt						; halt

section .bss
	resb 8192				; reserves 8KB of memory for the stack

stack:
