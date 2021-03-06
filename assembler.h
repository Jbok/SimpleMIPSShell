#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#define DATA 4096 //HEX 0x1000
#define TEXT 16384 //hex 0x4000
typedef struct s_code{
	char label[10];
	char instruction[15];
	char operand[64];
	int line;
	int text_line;
}s_code;


typedef struct symtab{
	char label[10];
	int value;
	int address;
}symtab;

typedef struct labtab{
	char label[10];
	int line;
}labtab;

//RESULT FILE;
FILE *rFile;

struct s_code code[512];
struct symtab tab[32];
struct labtab ltab[32];

char filename[255];
int line=0;
int text_line;
int text_size;
int data_size;
int tab_line;
#endif
