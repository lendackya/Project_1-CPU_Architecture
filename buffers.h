#include <stdio.h>
#include <stdlib.h>
#include <>


#ifndef BUFFERS
#define BUFFERS

typedef struct IF1_IF2{

	__int32_t instruction; 

} IF1_IF2;


typedef struct IF2_ID{

	__int32_t instruction;  
	
} IF2_ID;

typedef struct ID_EX1{

	// R-Type: 
		// 3 registers
		Rs
		Rt
		Rd	
	// J-Type: 
		target
		
	// I-Type: 
		immediate 
		
} ID_EX1;

typedef struct EX1_EX2{

	// R-Type: 
		Rs_data
		Rt_data
		Rd

	// I-Type: 
		immediate
		
	// J-Type:
		ALU_result
		

} EX1_EX2;

typedef struct EX2_MEM1{

	// R-Type: 
		Rs_data
		Rt_data
		Rd

	// I-Type: 
		immediate
		
	// J-Type:
		ALU_result

} EX2_MEM1;

typedef struct MEM1_MEM2{

	offset
	memory_data

} MEM1_MEM2;


typedef struct MEM2_WB
	
	mem_data
	offset
	write_back_reg

} MEM2_WB;

#endif