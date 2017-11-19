#include <stdio.h>
#include <string.h>
#include <math.h>
#include "instruction.h"

int *idec_to_bin(int idec){

	int isign=1;//plus
	int pbin[16];

	if(idec<0){
		isign=-1;//minus
		idec *= -1;
	}
	for (int i=0;i<16;i++){
		pbin[i]=idec%2;
		idec >>= 1;
	}
	if(isign==-1){
		for(int i=0; i<16;i++){
			(pbin[i]==0)?(pbin[i]=1):(pbin[i]=0);
		}
		pbin[0] += 1;
		for (int i=0; i<32-1;i++){
			if(pbin[i]==2){
				pbin[i]=0;
				pbin[i+1] += 1;
			}else{
				break;
			}
		}
	}
	int j=0;
	static int result[16];
	for(int i=15;i>=0;i--){
		result[j++]=pbin[i];
	}
	return result;
}

int hex_to_dec(char *hex){
	int dec=0;
	
	int position=0;
	for (int i=strlen(hex) -1; i>=0; i--){
		char ch=hex[i];
		
		if(ch>=48 && ch <=57){
			dec += (ch-48)*pow(16, position);
		} else if(ch>=65 && ch<=70){
			dec += (ch-(65-10))*pow(16, position);
		} else if(ch>=97 && ch<=102){
			dec += (ch-(97-10))*pow(16, position);
		}
		position++;
	}
	return dec;
}

int *binary_5bits(int dec){
	int temp[5]={0};
	int i, j;
	for(i=0; dec>0; i++){
		temp[i]=dec%2;
		dec=dec/2;
	}
	
	int k=0;
	static int result[5];

	for(j=4; j>=0; j--){
		result[k++]=temp[j];
	}
	return result;
}

int *binary_6bits(int dec){
	int temp[6]={0};
	int i, j;
	for(i=0; dec>0; i++){
		temp[i]=dec%2;
		dec=dec/2;
	}

	int k=0;
	static int result[6];

	for(j=5; j>=0; j--){
		result[k++]=temp[j];
	}
	return result;
}

int *binary_16bits(int dec){
	int temp[16]={0};
	int i, j;
	for(i=0; dec>0; i++){
		temp[i]=dec%2;
		dec=dec/2;
	}

	int k=0;
	static int result[16];

	for(j=15; j>=0; j--){
		result[k++]=temp[j];
	}
	return result;
}

int *I_format(int opcode, int rs, int rd, int se){
	static int result[32]={0};
	
	int *opcode_temp=binary_6bits(opcode);
	int opcode_temp_num=0;
	for(int i=0; i<6;i++){
		result[i]=opcode_temp[opcode_temp_num++];
	}

	int *rs_temp=binary_5bits(rs);
	int rs_temp_num=0;
	for(int i=6; i<11; i++){
		result[i]=rs_temp[rs_temp_num++];
	}

	int *rd_temp=binary_5bits(rd);
	int rd_temp_num=0;
	for(int i=11; i<16; i++){
		result[i]=rd_temp[rd_temp_num++];
	}

	int *se_temp=binary_16bits(se);
	int se_temp_num=0;
	for(int i=16; i<32; i++){
		result[i]=se_temp[se_temp_num++];
	}
	return result;
}

int *R_format(int opcode, int rs, int rt, int rd, int shamt, int funct){
	static int result[32]={0};
	
	int *opcode_temp=binary_6bits(opcode);
	int opcode_temp_num=0;
	for(int i=0; i<6;i++){
		result[i]=opcode_temp[opcode_temp_num++];
	}

	int *rs_temp=binary_5bits(rs);
	int rs_temp_num=0;
    for(int i=6; i<11; i++){
        result[i]=rs_temp[rs_temp_num++];
    }

    int *rt_temp=binary_5bits(rt);
    int rt_temp_num=0;
    for(int i=11; i<16; i++){
        result[i]=rt_temp[rt_temp_num++];
    }

    int *rd_temp=binary_5bits(rd);
    int rd_temp_num=0;
    for(int i=16; i<21; i++){
        result[i]=rd_temp[rd_temp_num++];
    }

	int *shamt_temp=binary_5bits(shamt);
	int shamt_temp_num=0;
	for(int i=21; i<26; i++){
		result[i]=shamt_temp[shamt_temp_num++];
	}

	int *funct_temp=binary_5bits(funct); 
    int funct_temp_num=0;
    for(int i=26; i<32; i++){
        result[i]=funct_temp[funct_temp_num++];
    }
	return result;
}



