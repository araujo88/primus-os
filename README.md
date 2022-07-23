<img src="print_screen.png"/>

# PrimusOS

A simple bare-bones 32-bit operating system written in Assembly x86 and C for educational purposes.

## Bootloader "hello world" example

### Compile bootloader

`nasm -o bootloader.bin bootloader.asm`

### Testing with QEmu

`qemu-system-x86_64 bootloader.bin`

## Compiling the kernel example

`gcc -c kernel.c -o kernel -ffreestanding -m32`

## Generating the ISO image

`make clean` <br>
`make primus-os.iso`
