#include "parser.h"
#include<stdio.h>
#include<stdlib.h>

// stream for source file
FILE *code;
// buffer for reading lines
char read_buf[256];
// line number for error printing

// returns only dest field, all gets return null if field is not present
char *get_dest(char *ins) {
char *dest = NULL;
int i = 0;
while(ins[i] != '=') {
	if(ins[i++] == '\0') {
		return dest;
		}
	}
dest = malloc(i*sizeof(char)+1);
dest[i] = '\0';
for(int d = 0; d < i; ++d) {
	dest[d] = ins[d];
}
return dest;
}

// returns only comp field
char* get_comp(char *ins) {
char *comp = NULL;
int equals_loc = 0;
while(ins[equals_loc] != '=') {
	if(ins[equals_loc++] == '\0') {
		equals_loc = 0;
		break;
		}
	}
int colon_loc = 0;
while(ins[colon_loc] != ';' && ins[colon_loc] != '\0')  {
	++colon_loc;
}
	
comp = malloc((colon_loc-equals_loc)*sizeof(char)+1);
comp[colon_loc-equals_loc] = '\0';
for(int d = 0; d < colon_loc; ++d) {
	comp[d] = ins[equals_loc+d+1];
}
return comp;
}

// parses jmp field, returns only jmp field
char* get_jmp(char *ins) {
char *jmp = NULL;
int i = 0;
while(ins[i] != ';') {
	if(ins[i++] == '\0') {
		return jmp;
		break;
		}
	}
jmp = malloc(3*sizeof(char)+1);
jmp[3] = '\0';
for(int d = 0; ins[i++]; ++d) {
	jmp[d] = ins[i];
}
return jmp;
}


// reads line containing instruction, stores it in ins
void read_instruction(char *ins) {
char c;
int i = 0;
int ins_counter = 0;
int slash_prev = 0;
fgets(read_buf,255,code);
while((c = read_buf[i++]) != '\n') {
	if(c != ' ' ) {
	ins[ins_counter++] = c;
	}
	if(c == '/') {
		if(slash_prev) {
			ins[ins_counter-2] = '\0';//stops here
			break;
		}
		slash_prev = 1;
	}
	else {
		slash_prev = 0;
	}
	}
	ins[ins_counter] = '\0';
}

// gets type of instruction
C_Type command_type(char *ins) {
		switch(ins[0]) {
		case '@':
		return A_COMMAND;
		case '(':
		return L_COMMAND;
		case '\0':
		return NO_COMMAND;
		default:
		return C_COMMAND;
	}
}

int open_source(char *file) {
	code = fopen(file,"r");
	if(!code) {
		return 1;
	}
	return 0;
}
int close_source() {
	fclose(code);
	return 0;
}

// checks for more input
bool has_next() {
	char c;
	if((c = fgetc(code))== EOF) {
		return false;
	}
	ungetc(c,code);
	return true;
}
