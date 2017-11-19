#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#define DATA 4096 //HEX 0x1000
#define TEXT 16384 //hex 0x4000
typedef struct s_code{
	char label[10];
	char instruction[15];
	char operand[64];
}s_code;


typedef struct symboltable{
	char label[10];
	int value;
	int address;
}symtab;


struct s_code code[512];
struct symtab symtab[32];
int line=0;
int text_size=0;
int data_size=0;
#endif
