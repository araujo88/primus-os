# my-first-os
My first operating system written in Assembly x86 and C

## Step 1

### Compile bootloader

nasm -o bootloader.bin bootloader.asm 

### Testing with QEmu

qemu-system-x86_64 bootloader.bin
