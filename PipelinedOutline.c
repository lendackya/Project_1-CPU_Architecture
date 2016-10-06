#include <stdio.h>
#include "BUFFERS.h"

int main(int argc, char *argv[]) {
	
	// Buffers
	IF1_IF2 IF1_IF2_buffer;
	IF2_ID IF2_ID_buffer; 
	ID_EX1 ID_EX1_buffer; 
	EX1_EX2 EX1_EX2_buffer; 
	EX2_MEM1 EX2_MEM1_buffer; 
	MEM1_MEM2 MEM1_MEM2_buffer; 
	MEM2_WB MEM_WB_buffer; 
	
	
	// Stage 1: Instruction Fetch 1
		// Get the instruction from the instruction memory
		// Increment PC by 4
		
		// store instruction in IF1_IF2_buffer
	
	// Stage 2: Instrcution Fetch 2
	
		// Do nothing 
		
		// Store instruction in IF2_ID_buffer
	
	// Stage 3: Instruction Decode
	
		// Get the opcode from the instruction 
			// Decode the opcode 
			// Determine is it is a R, I or J Type Instruction
		
		// Get corresonding values from registers depending on the type of instruction
	
		// Store the values in ID_EX1_buffer
		
		
	// Stage 4: Execution 1 
	
		// Based on opcode and sub-opcode, perform neccesary operation in ALU
		
		// Store the result in EX1_EX2_buffer
		
	// Stage 5: Execution 2
	
		// Do nothing 
		
		// Store the ALU Result in the EX2_MEM1_buffer
		
	// Stage 6: Access Memory 1 
	
		// If the instruction in a 'lw' or 'sw': 
			// write or retreive the value from memory
			
			// lw: base address (retrived from some register) + offset
			// sw: base address + offset
			
		// if lw: 
			// store the word in MEM1_MEM2_buffer
	
	// Stage 7: Access Memory 2
	
		// Do nothing
		
		// Store the word (if any) in MEM2_WB_buffer
	
	// Stage 8: Write Back 
	
		// Take ALU Result or word retrived from memeory and put into to correct regester
	
}