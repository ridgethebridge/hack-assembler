#include "decode.h"
#include "parser.h"
#include "constants.h"
#include "hashtable.h"
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


	
 extern int line_num;
 int var_address = 16;
bool are_equal(char *s1, char *s2) {
	if(strlen(s1) != strlen(s2)) {
		return false;
	}
while(*s1) {
	if(*s1++ != *s2++) {
		return false;
		}
	}
return true;
}

// gets index of field in array containing valid computation fields
int rank(char *field) {
	int lp = 0;
	int rp = sizeof(comp_pairs)/sizeof(struct C_Pairs)-1;
	int mid;

	while(lp <=rp) {
		mid = (lp+rp)/2;
		int cmp = strcmp(field,comp_pairs[mid].mnem);
		if(cmp < 0) {
			rp = mid-1;
		}
		else if(cmp > 0) {
			lp = mid+1;
		}
		else { return mid;}
	}
	return mid;
}

// gets index of field in array containing valid jumps
int rank_jmp(char *field) {
	int lp = 0;
	int rp = sizeof(jmp_pairs)/sizeof(struct C_Pairs)-1;
	int mid;

	while(lp <=rp) {
		mid = (lp+rp)/2;
		int cmp = strcmp(field,jmp_pairs[mid].mnem);
		if(cmp < 0) {
			rp = mid-1;
		}
		else if(cmp > 0) {
			lp = mid+1;
		}
		else { return mid;}
	}
	return mid;
}

// expects either a number or identifier, no @ included
void decode_a(char *d_ins, char *ins) {
int count = 15;
d_ins[16] = '\0';
memset(d_ins,'0',16);
if(isdigit(*ins)) {
	int value = atoi(ins);
	while(value >0) {
	d_ins[count--] = '0' +value%2;
	value/=2;
		}
	}
else if(isalpha(*ins) || *ins == '_')
	{
	int loc = get(ins);
	if(loc == -1) {
	loc = var_address++;
	put(ins,loc);
	}
	while(loc >0) {
	d_ins[count--] = '0' +loc%2;
	loc/=2;
		}
}
}

void decode_comp(char *d_ins, char *ins) {
	int rnk = rank(ins);
	if(are_equal(ins,comp_pairs[rnk].mnem)) {
	memcpy(d_ins,comp_pairs[rnk].opcode,7);
	}
	else {
	fprintf(stderr,"error in comp field, unknown operation, on line %d",line_num);
	fprintf(stderr," in statement %s\n",ins);
	exit(3);
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
	int rnk = rank_jmp(ins);
	if(are_equal(ins,jmp_pairs[rnk].mnem)) {
		strcpy(d_ins,jmp_pairs[rnk].opcode);
	}
	else {

		fprintf(stderr,"error in jump field, unknown directive on line %d",line_num);
		fprintf(stderr," in statement %s\n",ins);
		exit(3);
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

