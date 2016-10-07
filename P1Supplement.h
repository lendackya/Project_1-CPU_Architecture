//	P1Supplement.h
//	CoE 1541 Fall 2016 Project 1
//	Max Garber & Andrew Lendacky

//	#include-protect
#ifndef P1SUPPLEMENT
#define P1SUPPLEMENT

//	Headers
#include <stdint.h>
#include <stdio.h>

//	Types
typedef __uint8_t reg_addr;					//	register address (only 5b used)
typedef __int32_t register32_t;				//	register memory (32b)
typedef register32_t regfile32x32_t[32];	//	register file, 32 registers
typedef __uint32_t instruction_t;			//	instruction of unspecified type

typedef struct Rinstr_t {
	__uint8_t opcode:6;
	__uint8_t rs_addr:5;
	__uint8_t rt_addr:5;
	__uint8_t rd_addr:5;
	__uint8_t shamt:5;
	__uint8_t func:6;
} Rinstr_t;

typedef struct Iinstr_t {
	__uint8_t opcode:6;
	__uint8_t rs_addr:5;
	__uint8_t rt_addr:5;
	__uint16_t immediate:16;
} Iinstr_t;

typedef struct Jinstr_t {
	__uint8_t opcode:6;
	__uint64_t immediate:26;
} Jinstr_t;

//	Functions
void print_Rinstrxn(Rinstr_t instruxn) {
	printf("0x[%0.1X|", instruxn.opcode);
	printf("%0.1X|", instruxn.rs_addr);
	printf("%0.1X|", instruxn.rt_addr);
	printf("%0.1X|", instruxn.rd_addr);
	printf("%0.1X|", instruxn.shamt);
	printf("%0.1X]", instruxn.func);
	printf("\n");
}

void print_Iinstrxn(Iinstr_t instruxn) {
	printf("0x[%0.1X|", instruxn.opcode);
	printf("%0.1X|", instruxn.rs_addr);
	printf("%0.1X|", instruxn.rt_addr);
	printf("%0.2X]", instruxn.immediate);
	printf("\n");
}

void print_Jinstrxn(Jinstr_t instruxn) {
	printf("0x[%0.1X|", instruxn.opcode);
	printf("%0.4X]", instruxn.immediate);
	printf("\n");
}

void simulation_init() {
	
}

#endif
//EOFile
