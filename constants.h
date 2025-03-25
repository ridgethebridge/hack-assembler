
#ifndef CONSTANTS_H
#define CONSTANTS_H

// comp codes
#define ZERO "0"
#define ONE "1"
#define NEG_ONE "-1"
#define D "D"
#define A "A"
#define NOT_D "!D"
#define NOT_A "!A"
#define NEG_D "-D"
#define NEG_A "-A"
#define INC_D "D+1"
#define INC_A "A+1"
#define DEC_D "D-1"
#define DEC_A "A-1"
#define ADD "D+A"
#define SUB "D-A"
#define R_SUB "A-D"
#define AND "D&A"
#define OR "D|A"
#define M "M"
#define NOT_M "!M"
#define NEG_M "-M"
#define INC_M "M+1"
#define DEC_M "M-1"
#define M_ADD "D+M"
#define M_SUB "D-M"
#define RM_SUB "M-D"
#define M_AND "D&M"
#define M_OR "D|M"
#define R_ADD "A+D"
#define RM_ADD "M+D"

// jump codes
#define JMP "JMP"
#define JLT "JLT"
#define JLE "JLE"
#define JGT "JGT"
#define JGE "JGE"
#define JEQ "JEQ"
#define JNE "JNE"




struct C_Pairs {
char *mnem;
char *opcode;
};
// list of acceptable comp mnemonics and their binary values
static struct C_Pairs comp_pairs[] = {{NOT_A,"0110001"},{NOT_D,"0001101"},{NOT_M,"1110001"},{NEG_ONE,"0111010"},
					{NEG_A,"0110011"},{NEG_D,"0001111"},{NEG_M,"1110011"},{ZERO,"0101010"},
					{ONE,"0111111"},{A,"0110000"},{INC_A,"0110111"},{R_ADD,"0000010"},{DEC_A,"0110010"},
					{R_SUB,"0000111"},{D,"0001100"},{AND,"0000000"},{M_AND,"1000000"},{INC_D,"0011111"},
		   			{ADD,"0000010"},{M_ADD,"1000010"},{DEC_D,"0001110"},{SUB,"0010011"},{M_SUB,"1010011"},
		   			{OR,"0010101"},{M_OR,"1010101"},{M,"1110000"},{INC_M,"1110111"},{RM_ADD,"1000010"},{DEC_M,"1110010"},
		   			{RM_SUB,"1000111"}};

// list of acceptable jump mnemonics and their binary values
static struct C_Pairs jmp_pairs[7] = {{JEQ,"010"},{JGE,"011"},{JGT,"001"},{JLE,"110"},
				      {JLT,"100"},{JMP,"111"},{JNE,"101"}};

#endif
