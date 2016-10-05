#include <stdio.h>
#include <stdlib.h>
#include <>


#ifndef BUFFERS
#define BUFFERS

typedef struct IF1_IF2{

	__int32_t instruction; // the instruction that was fetched

} IF1_IF2;


typedef struct IF2_ID{

	__int32_t instruction; // the instruction that was fetched
	
} IF2_ID;

typedef struct ID_EX1{

		Rs // source register
		Rt // target register
		Rd // destination register

		target // target to branch to J-Type
		
		immediate // immediate value -> I-Type
		
} ID_EX1;

typedef struct EX1_EX2{

		Rs_data // data take from Rs register
		Rt_data // data taken from Rt register
		Rd // the destination register

		immediate // immediate value -> I-Type
		
		ALU_result // result from the ALU operation
		

} EX1_EX2;

typedef struct EX2_MEM1{

		Rs_data // data take from Rs register
		Rt_data // data taken from Rt register
		Rd // the destination register

		immediate // immediate value -> I-Type
		
		ALU_result // result from the ALU operation

} EX2_MEM1;

typedef struct MEM1_MEM2{

// Only used by lw and sw instructions

	offset // offset from the base addess -> lw and sw
	data_from_mem // data taken from memory -> lw
	data_to_mem // data stored into memory -> sw
	
// even though other insructions dont use memory, still need to pass it though the buffer
	Rd // the destination register to put ALU result in
	ALU_result // result from the ALU operation
	

} MEM1_MEM2;


typedef struct MEM2_WB
	
// Only used by lw and sw instructions

	offset // offset from the base addess -> lw and sw
	data_from_mem // data taken from memory -> lw
	data_to_mem // data stored into memory -> sw
	
// even though other insructions dont use memory, still need to pass it though the buffer
	Rd // the destination register to put ALU result in
	ALU_result // result from the ALU operation

} MEM2_WB;

#endif