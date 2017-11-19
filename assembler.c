#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char parsing_operand(int line){
	char op1[16];
	char op2[16];
	char op3[16];

	char buf[64];
	strcpy(buf,code[line].operand);
	printf("%s\n",buf);
	char *ptr=strtok(buf, " ,");	
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
		ptr=strtok(NULL," ,");
	}
	printf("op1:%s op2:%s op3:%s\n",op1,op2,op3);
	
	//////////////////////////////////////////////
	///         make address to integer        ///
	//////////////////////////////////////////////
	int op1_int;
	int op2_int;
	int op3_int;


	if(op1[0]=='$'){
		char *buf=strtok(op1,"$");
		strcpy(op1,buf);
		op1_int=atoi(op1);
	} else if(isalpha(op1[0])){
		op1_int=99999;
	} else if(op1[0]=='0' && op1[1]=='x'){ 
		char *buf;
		for(int i=2;i<strlen(op1);i++){
			buf[i-2]=op1[i];
		}
		printf("here %s ",buf);
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
		op2_int=161616;
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
		op2_int=161616;
	}else{
		op3_int=atoi(op3);
	}




	printf("%d, %d, %d\n", op1_int,op2_int,op3_int);
	//////////////////////////////////////////////
	///          Assembler function            ///
	//////////////////////////////////////////////
	if(!strcmp(code[line].instruction,"addiu")){
		//I_format(
	}
}

void printcode(){
	for (int i=0; i<line ;i++){
		
	}
}


int main(){
	read_file();
	for(int i=0; i<line; i++){
		printf("@label: %-10s instruction %-10s operand: %-10s\n",code[i].label,code[i].instruction,code[i].operand);
	}
	parsing_operand(3);
	return 0;
}
