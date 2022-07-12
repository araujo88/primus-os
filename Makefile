GCCPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions -ffreestanding -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.c
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

my-first-os.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

my-first-os.iso: my-first-os.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp my-first-os.bin iso/boot/my-first-os.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/my-first-os.bin' >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=my-first-os.iso iso
	rm -rf iso


install: my-first-os.bin
	sudo cp $< /boot/my-first-os.bin

clean:
	rm -f *.o my-first-os my-first-os.iso my-first-os.bin