#include "decode.h"
#include "parser.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define NOFILE_GIVEN 1
#define OPEN_FAILURE 2

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

int main(int argc, char** argv) {
	if(argc < 2) {
		fprintf(stderr,"must provide source file\n");
		return NOFILE_GIVEN;
	}
	if(open_source(argv[1])) {
		fprintf(stderr, "failed to open source file\n");
		return OPEN_FAILURE;
	}
	char ins[128];
	char d_ins[17];
	d_ins[16] = '\0';
	int ext_begin = dot_loc(argv[1]);
	char *out_file;
	if(ext_begin == -1) {
		size_t input_len = strlen(argv[1]);
		out_file = calloc(input_len+5,sizeof(char));
		memcpy(out_file,argv[1],input_len);
		strcpy(out_file+input_len,".hack");
	}
	else {
		out_file = calloc(ext_begin+5,sizeof(char));
		memcpy(out_file,argv[1],ext_begin);
		strcpy(out_file+ext_begin,".hack");
	}


	FILE *exe = fopen(out_file,"w");
	while(has_next()) {
		read_instruction(ins);
		switch(command_type(ins)) {
			case A_COMMAND:
				decode_a(d_ins,ins+1);
				break;
			case C_COMMAND:
				decode_c(d_ins,ins);
				break;
			case L_COMMAND:
			case NO_COMMAND:
				continue;
			}
		fprintf(exe,"%s\n",d_ins);
	}
	fclose(exe);
	close_source();
}

