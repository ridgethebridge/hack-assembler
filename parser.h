#ifndef PARSER_H
#define PARSER_H
#include<stdbool.h>
#include "hashtable.h"
typedef enum {
	A_COMMAND,
	C_COMMAND,
	L_COMMAND,
	NO_COMMAND
} C_Type;

typedef struct Parser {
const char* code;
const int length;
int cursor;
int line_num;
}Parser;

void read_line(char *ins,Parser* parser);
C_Type command_type(char *ins);
Parser* create_parser(char *file);
bool has_next(Parser* parser);
char* get_dest(char *ins);
char* get_comp(char *ins);
char *get_jmp(char *ins);
void fill_table(Parser *parser, Table* table);
void reset_parser(Parser *p);
void destroy_parser(Parser* parser);

#endif
