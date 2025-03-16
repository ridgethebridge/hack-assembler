#include "decode.h"
#include "parser.h"
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


	
int line_num = 0;
bool are_equal(char *s1, char *s2) {
while(*s1) {
	if(*s1++ != *s2++) {
		return false;
		}
	}
return true;
}
void decode_a(char *d_ins, char *ins) {
++line_num;
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
}
void decode_comp(char *d_ins, char *ins) {
for(int i = 0; i < sizeof(comp_pairs)/sizeof(struct C_Pairs); ++i) {
	if(are_equal(ins,comp_pairs[i].mnem)) {
		memcpy(d_ins,comp_pairs[i].opcode,7);
		return;
		}
	}
}

void decode_dest(char *d_ins, char *ins) {
	memset(d_ins,'0',3);
	if(!ins) {
		return;
	}
	int i = 0;
	while(ins[i]) {
		switch(ins[i]) {
		case 'A':
			d_ins[0] = '1';
			break;
		case 'M':
			d_ins[2] = '1';
			break;
		case 'D':
			d_ins[1] = '1';
			break;
		default:
		fprintf(stderr,"error in destination field, unknown dest %c, on line %d",ins[i],line_num);
		fprintf(stderr," in statement %s\n",ins);
		exit(3);
		}
		++i;
	}
}

void decode_jmp(char *d_ins,char *ins) {
	if(!ins) {
	memset(d_ins,'0',3);
		return;
	}
	for(int i = 0; i < sizeof(jmp_pairs)/sizeof(struct C_Pairs);++i) {
		if(are_equal(ins,jmp_pairs[i].mnem)) {
			strcpy(d_ins,jmp_pairs[i].opcode);
			return;
		}
	}
		fprintf(stderr,"error in jump field, unknown directive on line %d",line_num);
		fprintf(stderr," in statement %s\n",ins);
		exit(3);

}

void decode_c(char *d_ins,char *ins) {
strcpy(d_ins,"111");
++line_num;
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

