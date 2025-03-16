#ifndef PARSER_H
#define PARSER_H
#include<stdbool.h>
#include "constants.h"
typedef enum {
	A_COMMAND,
	C_COMMAND,
	L_COMMAND
} C_Type;
void read_instruction(char *ins);
C_Type command_type(char *ins);
int open_source(char *file);
bool has_next();
int close_source();
char* get_dest(char *ins);
char* get_comp(char *ins);
char *get_jmp(char *ins);
#endif
