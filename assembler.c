#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "assembler.h"
#include "instruction.h"


void read_file(){
	char filename[255];
	strcpy(filename,"./example3.s");	
	FILE *pFile =NULL;
	pFile=fopen(filename,"r");
	if(pFile != NULL){
		char strTemp[255];
		char *pStr;
		while(!feof(pFile)){
			pStr = fgets(strTemp, sizeof(strTemp), pFile);

			if(feof(pFile))
				break;

			int pStrnum=0;
			for(int i=0;i<3;i++){
				int ptrnum=0;
				while(1){
					if(pStr[pStrnum] != '\t' && pStr[pStrnum]!= '\n'){
						if(i==0){
							code[line].label[ptrnum]=pStr[pStrnum];
						}else if(i==1){
							code[line].instruction[ptrnum]=pStr[pStrnum];
						}else if(i==2){
							code[line].operand[ptrnum]=pStr[pStrnum];
						}else{
							fprintf(stderr,"Format Error\n");
							exit(1);
						}
						ptrnum++;
						pStrnum++;
					}else{
						if(i==0){
							code[line].label[ptrnum]='\0';
						}else if(i==1){
							code[line].instruction[ptrnum]='\0';
						}else if(i==2){
							code[line].operand[ptrnum]='\0';
						}else{
							fprintf(stderr,"Format Error\n");
							exit(1);
						}
						break;
					}
				}
				pStrnum++;
			}
			line++;
		}
	}else{
		fprintf(stderr,"Fille input error!\n");
	}
	fclose(pFile);	
}

void makesymboltable(){
	data_size=0;
	for (int i=0; i<line; i++){
		if(strcmp(code[i].instruction,".word")==0){
			strcpy(tab[data_size].label,code[i].label);
			tab[data_size].address= DATA+4*data_size;
      //change operand -> int
			char op1[32];
			int op1_int;
			strcpy(op1,code[i].operand);
			if(op1[0]=='$'){
				char *buf=strtok(op1,"$");
				strcpy(op1,buf);
				op1_int=atoi(op1);
			} else if(isalpha(op1[0])){
				op1_int=99999;
			} else if(op1[0]=='0' && op1[1]=='x'){ 
				char buf[16];
				for(int j=2;j<strlen(op1)+1;j++){
					buf[j-2]=op1[j];
				}
				printf("%s\n",op1);
				printf("%s\n",buf);
				op1_int=hex_to_dec(buf);
			}else{
				op1_int=atoi(op1);
			}	
			tab[data_size].value= op1_int;
			data_size++;	
		}
	}
}

void textsize(){
	text_size=0;
	for (int i=0;i<line;i++){
		if(!strcmp(code[i].instruction,"addiu")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"addu")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"and")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"andi")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"beq")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"bne")){	
			text_size++;
		}else if(!strcmp(code[i].instruction,"j")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"jal")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"jr")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"lui")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"lw")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"la")){
			if(!strcmp(code[i].label,tab[0].label)){
				text_size++;
			}else{//load address is 0x1000 0x0004
				text_size=text_size+2;
			}
		}else if(!strcmp(code[i].instruction,"nor")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"or")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"ori")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"sltiu")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"sltu")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"sll")){
				text_size++;
		}else if(!strcmp(code[i].instruction,"srl")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"sw")){
			text_size++;
		}else if(!strcmp(code[i].instruction,"subu")){
			text_size++;
		}else{
		}
	}
}

int address_word(char *argv){
	int address;
	for(int i=0;i<data_size;i++){
		if(!strcmp(argv,tab[i].label)){
			address=tab[i].address;
			return address;
		}
	}
}

void data_print(){
	int *print;
	for(int i=0; i<data_size; i++){
		//printf("tab[i].value %d \n", tab[i].value);
		print=binary_32bits(tab[i].value);
		for(int i=0; i<32; i++){
			printf("%d",print[i]);
		}
		printf("\n");
	}
}

void data_text_code_print(){
	int *text_code;
	int *data_code;

	text_code=binary_32bits(text_size*4);
	for(int i=0;i<32;i++){
		printf("%d",text_code[i]);
	}
	printf("\n");	

	data_code=binary_32bits(data_size*4);
	for(int i=0;i<32;i++){
		printf("%d",data_code[i]);
	}
	printf("\n");
}

void parsing_operand_print(int li){
	int flag=0;//print twice flag for la flag==0 not la, flag==1 la
	int *print;
	int *print_second;
	int temp[32]={0};

	char op1[16];
	char op2[16];
	char op3[16];

	char buf[64];
	strcpy(buf,code[li].operand);

	int emptyflag=0; //to prevent stack smashing
	if(!strcmp(buf,"")){
		emptyflag=1;
	}else{
		//printf("%-20s:",buf);
	}

	char *ptr=strtok(buf, " ,(");	
	int i=0;
	while (ptr!=NULL){
		if(i==0){
			strcpy(op1,ptr);
		}else if(i==1){
			strcpy(op2, ptr);
		}else if(i==2){
			strcpy(op3, ptr);
		}else{
			fprintf(stderr,"Format Error\n");
			exit(1);
		}
		i++;
		ptr=strtok(NULL," ,(");
	}
	
	//////////////////////////////////////////////
	///         make address to integer        ///
	//////////////////////////////////////////////
	int op1_int;
	int op2_int;
	int op3_int;

	if(emptyflag==0){
		if(op1[0]=='$'){
			char *buf=strtok(op1,"$");
			strcpy(op1,buf);
			op1_int=atoi(op1);
		} else if(isalpha(op1[0])){
			op1_int=99999;
		} else if(op1[0]=='0' && op1[1]=='x'){ 
			char buf[16];
			for(int i=2;i<strlen(op1)+1;i++){
				buf[i-2]=op1[i];
			}
			op1_int=hex_to_dec(buf);
		}else{
			op1_int=atoi(op1);
		}
	
		if(op2[0]=='$'){
			char *buf=strtok(op2,"$");
			strcpy(op2,buf);
			op2_int=atoi(op2);
		} else if(isalpha(op2[0])){
			op2_int=99999;
		} else if(op2[0]=='0' && op2[1]=='x'){ 
				char buf[16];
				for(int i=2;i<strlen(op2)+1;i++){
					buf[i-2]=op2[i];
				}
				op2_int=hex_to_dec(buf);
		}else{
			op2_int=atoi(op2);
		}
	
		if(op3[0]=='$'){
			char *buf=strtok(op3,"$");
			strcpy(op3,buf);
			op3_int=atoi(op3);
		} else if(isalpha(op3[0])){
			op2_int=99999;
		} else if(op3[0]=='0' && op3[1]=='x'){ 
			char buf[16];
			for(int i=2;i<strlen(op3)+1;i++){
				buf[i-2]=op3[i];
			}
			op3_int=hex_to_dec(buf);
		}else{
			op3_int=atoi(op3);
		}
	}



	//printf("%d, %d, %d\n", op1_int,op2_int,op3_int);
	//////////////////////////////////////////////
	///          Assembler function            ///
	//////////////////////////////////////////////
	if(!strcmp(code[li].instruction,"addiu")){
		print=I_format(9,op2_int,op1_int,op3_int);
	}else if(!strcmp(code[li].instruction,"addu")){
		print=R_format(0,op2_int,op3_int,op1_int,0,33);//hex:2,1 dec:33
	}else if(!strcmp(code[li].instruction,"and")){
		print=R_format(0,op2_int,op3_int,op1_int,0,36);//hex:2,4 dec:36
	}else if(!strcmp(code[li].instruction,"andi")){
		print=I_format(12,op2_int,op1_int,op3_int);//hex:c dec:12
	}else if(!strcmp(code[li].instruction,"beq")){
		print=I_format(4,op1_int,op2_int,op3_int);//hex:4 dec:4
	}else if(!strcmp(code[li].instruction,"bne")){
		print=I_format(5,op1_int,op2_int,op3_int);//hex:5 dec:5
	}else if(!strcmp(code[li].instruction,"j")){
		////
	}else if(!strcmp(code[li].instruction,"jal")){
		////
	}else if(!strcmp(code[li].instruction,"jr")){
		////
	}else if(!strcmp(code[li].instruction,"lui")){
		print=I_format(15,0,op1_int,op2_int);
	}else if(!strcmp(code[li].instruction,"lw")){
		print=I_format(35,op3_int,op1_int,op2_int);//hex:2,3 dec:35
	}else if(!strcmp(code[li].instruction,"la")){
		if(!strcmp(code[li].label,tab[0].label)){
			print=I_format(15,0,op1_int,4096);//lui - 0x1000: 4096
		}else{//load address is 0x1000 0x0004
			print=I_format(15,0,op1_int,4096);//lui - 0x1000: 4096
			flag=1;
			//check word_address
			int k;
			for(k=0;k<data_size;k++){
				if(!strcmp(code[li].label,tab[k].label)){
					break;
				}
			}
			print_second=I_format(13,op1_int,op1_int,(tab[k].address-4096)*4);//ori - 0x0004: 4
		}
	}else if(!strcmp(code[li].instruction,"nor")){
		print=R_format(0,op2_int,op3_int,op1_int,0,39);//hex2,7
	}else if(!strcmp(code[li].instruction,"or")){
		print=R_format(0,op2_int,op3_int,op1_int,0,37);//hex2,5 
	}else if(!strcmp(code[li].instruction,"ori")){
		print=I_format(13,op1_int,op2_int,op3_int);//hex:d dec13
	}else if(!strcmp(code[li].instruction,"sltiu")){
		print=I_format(13,op2_int,op1_int,op3_int);//hex:b dec11
	}else if(!strcmp(code[li].instruction,"sltu")){
		print=R_format(0,op2_int,op3_int,op1_int,0,43);//hex:2,b dec43
	}else if(!strcmp(code[li].instruction,"sll")){
		print=R_format(0,0,op2_int,op1_int,op3_int,0);//hex0 d0
	}else if(!strcmp(code[li].instruction,"srl")){
		print=R_format(0,0,op2_int,op1_int,op3_int,2);//hex2 d2
	}else if(!strcmp(code[li].instruction,"sw")){
		print=I_format(43,op3_int,op1_int,op2_int);//hex2,b d53
	}else if(!strcmp(code[li].instruction,"subu")){
		print=R_format(0,op2_int,op3_int,op1_int,0,35);//hex2,3 d35
	}/*else if(!strcmp(code[li].instruction,".word")){
		print=binary_32bits(op1_int);
	}*/else{
		return;
	}


	/////////////////////////////////////
	///          print result         ///
	/////////////////////////////////////
	for(int i=0;i<32;i++){
		printf("%d",print[i]);
	}
	printf("\n");
	
	if (flag==1){
		for(int i=0;i<32;i++){
			printf("%d",print_second[i]);
		}
		printf("\n");	
	}
	
}



int main(){
	read_file();
	printf("%d",line);	
/*	for(int i=0; i<line; i++){
		printf("line:%d label: %-10s instruction %-10s operand: %-10s\n",i,code[i].label,code[i].instruction,code[i].operand);
	}*/
	//sybmol table teset
	makesymboltable();
	for(int i=0;i<data_size;i++){
		printf("label: %s value: %d address: %d \n",tab[i].label, tab[i].value, tab[i].address);
	}
	
	//text size test
	textsize();
	data_text_code_print();


	//text print test
	for(int i=data_size+2; i<line; i++){
		parsing_operand_print(i);
	}
	
	//data print test
	data_print();

	return 0;
}
