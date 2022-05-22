CC = nasm
compile: main.asm
	${CC} -g -f elf -o main.o -l main.list main.asm
	ld -m elf_i386 -o main main.o
run: main
	./main
start: compile run
debug: main
	gdb -q -x main.gdb