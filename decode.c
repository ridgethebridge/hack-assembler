#include "decode.h"
#include "parser.h"
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

#define ZERO "0"
#define ONE "1"
#define NEG_ONE "-1"
#define D "D"
#define A "A"
#define NOT_D "!D"
#define NOT_A "!A"
#define NEG_D "-D"
#define NEG_A "-A"
#define INC_D "D+1"
#define INC_A "A+1"
#define DEC_D "D-1"
#define DEC_A "A-1"
#define ADD "D+A"
#define SUB "D-A"
#define R_SUB "A-D"
#define AND "D&A"
#define OR "D|A"
#define M "M"
#define NOT_M "!M"
#define NEG_M "-M"
#define INC_M "M+1"
#define DEC_M "M-1"
#define M_ADD "D+M"
#define M_SUB "D-M"
#define RM_SUB "M-D"
#define M_AND "D&M"
#define M_OR "D|M"

Table sym_table = {NULL, 23};
struct Comp_Pairs {
char *mnem;
char *opcode;
};
struct Comp_Pairs pairs[27] = {{ZERO,"0101010"},{ONE,"0111111"},{NEG_ONE,"0111010"},{D,"0001100"},{A,"0110000"},{NOT_D,"0001101"},
		   {NOT_A,"0110001"},{NEG_D,"0001111"},{INC_D,"0011111"},{INC_A,"0110111"},{DEC_D,"0001110"},{DEC_A,"0110010"},
		   {ADD,"0000010"},{SUB,"0010011"},{R_SUB,"0000111"},{AND,"0000000"},{OR,"0010101"},{M,"111000"},{NOT_M,"1110001"},
		   {NEG_M,"1110011"},{INC_M,"1110111"},{DEC_M,"1110010"},{M_ADD,"1000010"},{M_SUB,"1010011"},{RM_SUB,"1000111"},
		   {M_AND,"1000000"},{M_OR,"1010101"}};

	
bool are_equal(char *s1, char *s2) {
while(*s1) {
	if(*s1++ != *s2++) {
		return false;
		}
	}
return true;
}
void decode_a(char *d_ins, char *ins) {
if(isdigit(*ins)) {
	int value = atoi(ins+1);
	memset(d_ins,'0',16);
	d_ins[16] = '\0';
	int count = 15;
	while(value >= 1) {
	d_ins[count--] = '0' +value%2;
	value/=2;
		}
	}
else 
	{

}
void decode_comp(char *d_ins, char *ins) {
for(int i = 0; i < sizeof(pairs)/sizeof(struct Comp_Pairs); ++i) {
	if(are_equal(ins,pairs[i].mnem)) {
		memcpy(d_ins,pairs[i].opcode,7);
		return;
		}
	}
}

void decode_dest(char *d_ins, char *ins) {
	memset(d_ins,'0',3);
	if(!ins) {
		return;
	}
	while(*ins) {
		switch(*ins++) {
		case 'A':
			d_ins[0] = '1';
			break;
		case 'M':
			d_ins[2] = '1';
			break;
		case 'D':
			d_ins[1] = '1';
			break;
		}
	}
}

void decode_jmp(char *d_ins,char *ins) {
	if(!ins) {
	memset(d_ins,'0',3);
		return;
	}
	switch(ins[0] + ins[1] + ins[2]) {
	case JMP:
		strcpy(d_ins,"111");
		break;
	case JLT:
		strcpy(d_ins,"100");
		break;
	case JGT:
		strcpy(d_ins,"001");
		break;
	case JEQ:
		strcpy(d_ins,"010");
		break;
	case JGE:
		strcpy(d_ins,"011");
		break;
	case JNE:
		strcpy(d_ins,"101");
		break;
	case JLE:
		strcpy(d_ins,"110");
		break;
		}
}

void decode_c(char *d_ins,char *ins) {
strcpy(d_ins,"111");
d_ins+=3;
char *dest = get_dest(ins);
char *jmp = get_jmp(ins);
char *comp = get_comp(ins);
decode_comp(d_ins,comp);
d_ins+=7;
decode_dest(d_ins,dest);
d_ins+=3;
decode_jmp(d_ins,jmp);
free(dest);
free(jmp);
free(comp);
}

