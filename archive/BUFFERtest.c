#include "BUFFERS.h"
#include "P1Supplement.h"

int main(int argc, char *argv[]) {
	
	IF1_IF2 buffer_one; 
	
	// fetched instn
	instruction_t instruction = 0xB103419A; 
		
	buffer_one.instruction = instruction;
	
	printf("IF1/IF2-instruction: %X\n",  buffer_one.instruction ); 
	
	IF2_ID buffer_two; 
	buffer_two.instruction = instruction; 
		
	printf("IF2/ID-instruction: %X\n",  buffer_two.instruction ); 
	
	// decode and assign to type 
	
	Rinstr_t r_type; 
	r_type.opcode =  0xB; 
	
}