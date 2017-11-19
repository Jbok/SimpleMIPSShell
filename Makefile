test : assembler.o instruction.o
	gcc -o test assembler.o instruction.o -lm

assembler.o : assembler.c
	gcc -c -o assembler.o assembler.c

instruction.o : instruction.c
	gcc -c -o instruction.o instruction.c

clean :
	rm *.o test
