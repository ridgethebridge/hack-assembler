#include "parser.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

// maybe fill table when creating parser, have to pass through file one less
void fill_table(Parser * parser,Table* table) {
char ins[128];
int rom_loc = 0;
put("R0",0,table);
put("R1",1,table);
put("R2",2,table);
put("R3",3,table);
put("R4",4,table);
put("R5",5,table);
put("R6",6,table);
put("R7",7,table);
put("R8",8,table);
put("R9",9,table);
put("R10",10,table);
put("R11",11,table);
put("R12",12,table);
put("R13",13,table);
put("R14",14,table);
put("R15",15,table);
put("SCREEN",16384,table);
put("KBD",24576,table);
while(has_next(parser)) {
read_line(ins,parser);
switch(command_type(ins)) {
case A_COMMAND:
case C_COMMAND:
++rom_loc;
break;
case L_COMMAND:
int par_loc = strlen(ins)-1;
if(ins[par_loc] != ')') {
	fprintf(stderr,"expected ) for label in line %d in statement %s\n",parser->line_num,ins);
	exit(1);
}
ins[strlen(ins)-1] = '\0';
put(ins+1,rom_loc,table);
break;
}

}
reset_parser(parser);
}


// reads line containing instruction, stores it in ins
void read_line(char *line,Parser* parser) {
#define FINISH(p) while(p->code[p->cursor++] != '\n');
	
char c;
int slash_prev = 0;
int letter_count = 0;
while((c = parser->code[parser->cursor++]) != '\n') {
	if(c != ' ' ) {
	line[letter_count++] = c;
	}
	if(c == '/') {
		if(slash_prev) {
			line[letter_count-2] = '\0';//stops here
			FINISH(parser)
			break;
		}
		slash_prev = 1;
	}
	else {
		slash_prev = 0;
	}
	}
	line[letter_count] = '\0';
	parser->line_num++;
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

Parser* create_parser(char *file) {
	#define INIT_SIZE 1024
	FILE* code = fopen(file,"r");
	if(!code) {
		return NULL;
	}
	size_t size = INIT_SIZE;
	char *source=malloc(sizeof(char)*size);
	size_t num_read = 0;
	char *line;
	// loads entire file into memory
	while((line=fgets(source+num_read,256,code))) {
		num_read+= strlen(line);
		if(size-num_read < 256) {
			size*=2;
			source = realloc(source,size);
		}
	}
	fclose(code);
	//shrinks down source size
	source = realloc(source,size);
	// only do this to initlize const field
	Parser *parser = malloc(sizeof(Parser));
	Parser p = {.code = source,.length=strlen(source),.cursor=0,.line_num=0};
	memcpy(parser,&p,sizeof(Parser));

	return parser;
}

// checks for more input
bool has_next(Parser* parser) {
	return parser->cursor < parser->length;
}

void reset_parser(Parser *parser) {
	parser->cursor = 0;
	parser->line_num = 0;
}
//frees parser and its contents, unusable unless set a new value
void destroy_parser(Parser *parser) {
	free((void*)parser->code);
	free(parser);
}
