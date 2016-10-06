//	header

//	includes

#ifndef P1CPU_REGISTERS
#define P1CPU_REGISTERS

//	declarations


// types for
// register address (5b)
// register itself (32b)
// register file (32x32b)

typedef char reg32_addr;
typedef __int32_t reg32;
typedef __int32_t regfile32x32[32];


#endif
//EOFile

#ifndef P1CPU_INSTRUCTIONS
#define P1CPU_INSTRUCTIONS

typedef __uint32_t instruction; 

typedef struct R_type_instruction {
	char opcode:8;
	reg32_addr rs_addr:8;
	reg32_addr rt_addr:8;
	reg32_addr rd_addr:8;
	char shamt:8;
	char func:8;
} R_type_instruction;

typedef struct I_type_instruction {
	char opcode:8;
	reg32_addr rs_addr:8;
	reg32_addr rt_addr:8;
	__uint16_t imm:16;
} I_type_instruction;


typedef struct J_type_instruction {


} J_type_instruction;

#endif
