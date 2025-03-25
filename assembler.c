#include "decode.h"
#include "parser.h"
#include "hashtable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define NOFILE_GIVEN 1
#define OPEN_FAILURE 2

// gets startof extension if there is one
int dot_loc(char *file) {
	int i = 0;
	while(file[i]) {
		if(file[i] == '.') {
			return i;
		}
		++i;
	}
	return -1;
}

// gets string prog.hack from prog.asm
char *get_output_name(char *file) {
	char *out_file;
	int ext_begin = dot_loc(file);
	if(ext_begin == -1) {
		size_t input_len = strlen(file);
		out_file = calloc(input_len+5,sizeof(char));
		memcpy(out_file,file,input_len);
		strcpy(out_file+input_len,".hack");
	}
	else {
		out_file = calloc(ext_begin+5,sizeof(char));
		memcpy(out_file,file,ext_begin);
		strcpy(out_file+ext_begin,".hack");
	}
	return out_file;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		fprintf(stderr,"must provide source file\n");
		return NOFILE_GIVEN;
	}
	Parser* parser = create_parser(argv[1]);
	// failed to create parser for file
	if(!parser) {
		fprintf(stderr, "failed to open source file\n");
		return OPEN_FAILURE;
	}
	char ins[128];
	char d_ins[17];
	d_ins[16] = '\0';
	Table *table = create_table(23);
	fill_table(parser,table);


	FILE *exe = fopen(get_output_name(argv[1]),"w");
	while(has_next(parser)) {
		read_line(ins,parser);
		switch(command_type(ins)) {
			case A_COMMAND:
				decode_a(d_ins,ins+1,table);
				break;
			case C_COMMAND:
				decode_c(d_ins,ins);
				break;
			default:
				continue;
			}
		fprintf(exe,"%s\n",d_ins);
	}
	fclose(exe);
	destroy_parser(parser);
}

