#include "BUFFERS.h"
#include "P1CPU.h"

int main(int argc, char *argv[]) {
	
	IF1_IF2 buffer_one; 
	
	// fetched instn
	instruction instruction = 0xB103419A; 
		
	buffer_one.instruction = instruction;
	
	printf("IF1/IF2-instruction: %x\n",  buffer_one.instruction ); 
	
	IF2_ID buffer_two; 
	buffer_two.instruction = instruction; 
		
	printf("IF2/ID-instruction: %x\n",  buffer_two.instruction ); 
	
	// decode and assign to type 
	
	R_type_instruction r_type; 
	r_type.opcode = (char) 0xB; 
	
}