nasm -f elf bootloader.asm -o bootloader.o
g++ -w -fpermissive -m32 -fno-stack-protector -c kernel.cpp -o cppkernel.o
nasm -f elf includes/realmode.asm -o realmode.o
# experimental file (for opcodes)
nasm -f bin experimentFile.asm -o exp.bin

ld -m elf_i386 -T link.ld -o kernel.bin bootloader.o realmode.o cppkernel.o 
grub-mkrescue -o AwkieOS.iso ./
qemu-system-i386 -kernel ./kernel.bin

# cleanup :)
rm -r *.o
rm -r *.bin
rm -r *.out