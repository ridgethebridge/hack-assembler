#ifndef DECODE_H
#define DECODE_H
#include "hashtable.h"
 void decode_dest(char *d_ins, char*ins);
 void decode_comp(char *d_ins, char*ins);
 void decode_jmp(char *d_ins, char *ins);
 void decode_c(char *d_ins, char *ins);
void decode_a(char *d_ins, char *ins,Table *table);
#endif
