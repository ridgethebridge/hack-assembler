#ifndef DECODE_H
#define DECODE_H
#define JMP ('J'+'M'+'P')
#define JLT ('J'+'L'+'T')
#define JLE ('J'+'L'+'E')
#define JGT ('J'+'G'+'T')
#define JGE ('J'+'G'+'E')
#define JEQ ('J'+'E'+'Q')
#define JNE ('J'+'N'+'E')


 void decode_dest(char *d_ins, char*ins);
 void decode_comp(char *d_ins, char*ins);
 void decode_jmp(char *d_ins, char *ins);
 void decode_c(char *d_ins, char *ins);
void decode_a(char *d_ins, char *ins);
#endif
