echo -e "compiling c modules..."
# compile C files
for i in lib/*.c lib/*.cpp ; do
	printf "compiling %s..." $i
	gcc -w -c -o $i.o -fno-stack-protector -m32 -ffreestanding -nostdlib $i -I lib 2> outfile
	if [[ $(cat outfile) != "" ]] ; then
		echo -e "\n\n------ BUILD FAILED! ------";
		cat outfile
		exit
	fi
	printf " done! (%s.o)\0\n" $i
	
done

echo -e "\ncompiling assembly modules..."
# compile assembly files
for i in lib/*.asm ; do
	printf "compiling %s..." $i
	nasm -felf -o $i.o $i 2> outfile
	if [[ $(cat outfile) != "" ]] ; then
		echo -e "\n\n------ BUILD FAILED! ------";
		cat outfile
		exit
	fi
	printf " done! (%s.o)\0\n" $i
done

echo -e "\nverifying..."
for i in lib/*.asm lib/*.c ; do
	if [[ ! -f "$i.o" ]] ; then
		printf "Error: File not found, did it compile? (%s.o)\n" $i
	fi
done

printf "compiling main source files..."
# compile kernel and assembly stub for GRUB
nasm -felf src/boot.asm -o src/boot.o
gcc -m32 src/main.c -c -o src/main.o -w -ffreestanding -nostdlib -fno-stack-protector -I lib

printf " done! (src/boot.o & src/main.o)\0\n"
printf "linking compiled source..."
# link compiled files together
ld -o Kernel -T src/link.ld -m elf_i386 src/boot.o src/main.o lib/*.o 
printf " done! (Kernel)\0\n"

printf "removing old object files..."
rm -f */*.o
rm -f outfile
printf " done!\0\n"

mv Kernel out

echo "kernel compiled"
printf "do you want to launch qemu? [y/N]: "
read conf

# no is default
if [[ $conf != "y" ]] ; then
	exit 
fi

qemu-system-i386 -kernel out/Kernel

