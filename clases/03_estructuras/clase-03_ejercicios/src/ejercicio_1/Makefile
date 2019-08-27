all:
	nasm -f elf64 -g -F dwarf -o ejercicio.o ejercicio.asm
	gcc -no-pie -fno-pie -o ejercicio -m64 -ggdb main.c  ejercicio.o

clean:
	rm -f *~ ejercicio *.o
