# my-first-os

My first operating system written in Assembly x86 and C

## Bootloader

### Compile bootloader

nasm -o bootloader.bin bootloader.asm

### Testing with QEmu

qemu-system-x86_64 bootloader.bin

## Compiling the kernel

gcc -c kernel.c -o kernel -ffreestanding -m32

## Gerating the ISO image

make my-first-os.iso
