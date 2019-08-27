all: ejercicio_con_asm ejercicio_con_c

ejercicio_con_asm:
	nasm -f elf64 -g -F dwarf -o ejercicio.o ejercicio.asm
	gcc -no-pie -fno-pie -o ejercicio_con_asm -m64 -ggdb main.c ejercicio.o

ejercicio_con_c:
	gcc -no-pie -fno-pie -o ejercicio_con_c -m64 -ggdb main.c ejercicio.c

clean:
	rm -f *~ ejercicio_con_c ejercicio_con_asm *.o
