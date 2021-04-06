nasm -f elf bootloader.asm -o bootloader.o
gcc -m32 -c kernel.cpp -o cppkernel.o

ld -m elf_i386 -T link.ld -o kernel.bin bootloader.o cppkernel.o
grub-mkrescue -o AwkieOS.iso ./
qemu-system-i386 -kernel ./kernel.bin

# cleanup :)
rm -r *.o
rm -r *.bin
rm -r *.out