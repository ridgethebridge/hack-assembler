/* TODO
-the read_instruction function can read past designated array
*/

#include "parser.h"
#include "hashtable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// stream for source file
FILE *code;
// buffer for reading lines
char read_buf[256];
// line number for error printing
int line_num = 0;

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
int comp_start = 0;
while(ins[comp_start] != '=') {
	if(ins[comp_start++] == '\0') {
		comp_start = -1;
		break;
		}
	}
++comp_start;
int colon_loc = comp_start+1;
while(ins[colon_loc] != ';' && ins[colon_loc] != '\0')  {
	++colon_loc;
}
int comp_length = colon_loc - comp_start;
	
comp = malloc((comp_length)*sizeof(char)+1);
comp[comp_length] = '\0';
for(int d = 0; d < comp_length; ++d) {
	comp[d] = ins[comp_start+d];
}
return comp;
}

// returns only jmp field
char* get_jmp(char *ins) {
	char *jmp = NULL;
	int i = 0;
	while(ins[i] != ';') 
	{
		if(ins[i++] == '\0') {
			return jmp;
		}
	}
	jmp = malloc(3*sizeof(char)+1);
	jmp[3] = '\0';
	for(int d = 0; ins[i++]; ++d) {
		jmp[d] = ins[i];
		}	
	return jmp;
}

void fill_table() {
char ins[128];
int rom_loc = 0;
while(has_next()) {
read_instruction(ins);
switch(command_type(ins)) {
case A_COMMAND:
case C_COMMAND:
++rom_loc;
break;
case L_COMMAND:
int par_loc = strlen(ins)-1;
if(ins[par_loc] != ')') {
	fprintf(stderr,"expected ) for label in line %d in statement %s\n",line_num,ins);
	exit(1);
}
ins[strlen(ins)-1] = '\0';
put(ins+1,rom_loc);
break;
}

}
rewind(code);
line_num = 0;
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
	++line_num;
}

// gets type of instruction
C_Type command_type(char *ins) {
		switch(ins[0]) {
		case '@':
		return A_COMMAND;
		case '(':
		return L_COMMAND;
		case '\n':
		case '\0':
		return NO_COMMAND;
		default:
		return C_COMMAND;
	}
}

// 1 on failure, 0 on success
int open_source(char *file) {
	code = fopen(file,"r");
	if(!code) {
		return 1;
	}
	create_table(TABLE_SIZE);
	fill_table();
	return 0;
}
int close_source() {
	fclose(code);
	return 0;
}

// checks for more input
bool has_next() {
char c = getc(code);
if(c == EOF)
	return false;
ungetc(c,code);
return true;
}
