#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

int *idec_to_bin(int idec);
int hex_to_dec(char *hex);
int *binary_5bits(int dec);
int *binary_6bits(int dec);
int *binary_16bits(int dec);
int *binary_32bits(int dec)
int *I_format(int opcode, int rs, int rd, int se);
int *R_format(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *J_format(int opcdoe, int address);
//I-format
int *ADDIU(int opcode, int rs, int rd, int se);
int *ANDI(int opcode, int rs, int rd, int se);
int *BEQ(int opcode, int rs, int rd, int se);
int *BNE(int opcode, int rs, int rd, int se);
int *LUI(int opcode, int rs, int rd, int se);
int *LW(int opcode, int rs, int rd, int se);
int *ORI(int opcode, int rs, int rd, int se);
int *SLTIU(int opcode, int rs, int rd, int se);
int *SW(int opcode, int rs, int rd, int se);

//R-format
int *ADDU(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *AND(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *JR(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *NOR(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *OR(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *SLTU(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *SLL(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *SRL(int opcode, int rs, int rt, int rd, int shamt, int funct);
int *SUBU(int opcode, int rs, int rt, int rd, int shamt, int funct);


//J-format
int *J;
int *JAL;


int *LA;

#endif
