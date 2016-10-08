#include <stdio.h>
#include <stdlib.h>
#include "P1Supplement.h"


#ifndef BUFFERS
#define BUFFERS

// 26 bit integer
typedef struct __uint26_t{
    unsigned int data : 26;
} __uint26_t;

typedef struct IF1_IF2{

	instruction_t instruction; // the instruction that was fetched

} IF1_IF2;


typedef struct IF2_ID{

	instruction_t instruction; // the instruction that was fetched
	
} IF2_ID;

typedef struct ID_EX1{

    reg_addr Rs; // source register
    reg_addr Rt; // target register
    reg_addr Rd; // destination register

    __uint26_t target; // target to branch to J-Type
		
    __uint16_t immediate; // immediate value -> I-Type
		
} ID_EX1;

typedef struct EX1_EX2{

    register32_t Rs_data; // data take from Rs register
    register32_t Rt_data; // data taken from Rt register
    register32_t Rd; // the destination register

    __uint16_t immediate; // immediate value -> I-Type
		
    register32_t ALU_result; // result from the ALU operation
		

} EX1_EX2;

typedef struct EX2_MEM1{

    register32_t Rs_data; // data take from Rs register
    register32_t Rt_data; // data taken from Rt register
    register32_t Rd; // the destination register

    __uint16_t immediate; // immediate value -> I-Type
		
    register32_t ALU_result; // result from the ALU operation

} EX2_MEM1;

typedef struct MEM1_MEM2{

// Only used by lw and sw instructions

    __uint16_t offset; // offset from the base addess -> lw and sw
    register32_t data_from_mem; // data taken from memory -> lw
    register32_t data_to_mem ;// data stored into memory -> sw
	
// even though other insructions dont use memory, still need to pass it though the buffer
    reg_addr Rd ;// the destination register to put ALU result in
    register32_t ALU_result; // result from the ALU operation
	

} MEM1_MEM2;


typedef struct MEM2_WB{
	
// Only used by lw and sw instructions

    __uint16_t offset; // offset from the base addess -> lw and sw
    register32_t data_from_mem; // data taken from memory -> lw
    register32_t data_to_mem; // data stored into memory -> sw
	
// even though other insructions dont use memory, still need to pass it though the buffer
    register32_t Rd; // the destination register to put ALU result in
    register32_t ALU_result; // result from the ALU operation

} MEM2_WB;

#endif
