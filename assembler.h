#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

typedef struct s_code{
	char label[10];
	char instruction[15];
	char operand[64];
}s_code;

typedef struct symboltable{
	char label[10];
	char instruction[10];
}symtab;


struct s_code code[512];
int line=0;
int text_size=0;
int data_size=0;
#endif
