
echo > outfile

function compile_c {
	echo "compiling C/++ modules..."
	# compile C files
	for i in lib/*.c lib/*.cpp ; do
		printf "compiling %s..." $i
		gcc -w -c -o $i.o -fno-stack-protector -m32 -ffreestanding -nostdlib $i -I lib 2> outfile
		if [[ $(cat outfile) != "" ]] ; then
			echo -e "\n\n------ BUILD FAILED! ------";
			cat outfile
			ERROR;
		fi
		printf " done! (%s.o)\0\n" $i
	done
}
function compile_s {
	echo -e "\ncompiling assembly modules..."
	# compile assembly files
	for i in lib/*.asm ; do
		printf "compiling %s..." $i
		nasm -felf -o $i.o $i 2> outfile
		if [[ $(cat outfile) != "" ]] ; then
			ERROR
		fi
		printf " done! (%s.o)\0\n" $i
	done
}
function compile_all {
	printf "compiling main source files..."
	# compile kernel and assembly stub for GRUB
	nasm -felf src/boot.asm -o src/boot.o
	gcc -m32 src/main.c -c -o src/main.o -w -ffreestanding -nostdlib -fno-stack-protector -I lib

	printf " done! (src/boot.o & src/main.o)\0\n"
	printf "linking compiled source..."
	# link compiled files together
	ld -o out/Kernel -T src/link.ld -m elf_i386 src/boot.o src/main.o lib/*.o > outfile
	if [[ $(cat outfile) != "" ]] ; then
		ERROR
	fi
	printf " done! (out/Kernel)\n"
}

function cleanup {
	rm -f */*.o
}

function ERROR {
	echo -e "\n\n------ BUILD FAILED! ------"
	cat outfile
	cleanup
	exit
}
function vm_search {
	if [[ $(whereis qemu-system-i386) == "qemu-system-i386:" ]] ; then
		echo "you need to install QEMU so you can test the operating system!!!" > outfile
		ERROR
	fi
	printf "do you want to launch qemu? [y/N]: "
	read conf

	# no is default
	if [[ $conf != "y" ]] ; then
		exit 
	fi

	qemu-system-i386 -kernel out/Kernel
}

compile_c
compile_s
compile_all

printf "removing old object files..."
cleanup
printf "done!\0\n"

echo "kernel compiled"
vm_search
