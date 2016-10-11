
#include "PipelinedCPU.h"
#include <string.h>

#ifndef HAZARD_CONTROL
#define HAZARD_CONTROL

// GLOBAL FLAGS
bool STRUCTURAL_HAZARD_FLG = false; 
bool DATA_HAZARD_FLG_ONE = false; 
bool DATA_HAZARD_FLG_TWO = false; 
bool DATA_HAZARD_FLG_THREE = false; 
bool CONTROL_HAZARD_FLG = false; 

// Checks if the instruction in the given stage is a 'Write' instruction
bool will_write_to_reg(int stage){
	
	if (strcmp(pipeline[stage].type, "RTYPE") == 0 || strcmp(pipeline[stage].type, "LOAD") == 0 || strcmp(pipeline[stage].type, "ITYPE") == 0)){ return true; }
		
	return false; 
}

// Checks if the instuction in the given stage is a 'Read' instruction
bool will_read_from_reg(int stage){

	if (strcmp(pipeline[stage].type, "RTYPE") == 0 || strcmp(pipeline[stage].type, "ITYPE") == 0 || strcmp(pipeline[stage].type, "BRANCH") == 0)){ return true; }
	
	return false; 
}

// Checks if the instruction in the given stage will read from memory
bool will_read_from_memory(int stage){
	
	if (strcmp(pipeline[stage].type, "LOAD") == 0 ){ return true; }
	
	return false; 	
}

// Checks if the instruction in the given stage will write to memory 
bool will_write_to_memory(int stage){
	
	if (strcmp(pipeline[stage].type, "STORE") == 0 ){ return true; }
	
	return false; 	
}

void check_hazards(){
	
	// Data Hazards: 
		
		// (a) If an instruction in EX1 will write into a register while the instruction in ID is reading from register X, ...
		if (will_write_to_reg(3) && will_read_from_reg(2)){
			
			if ((pipeline[3].rd == pipeline[2].rs) || (pipeline[3].rd == pipeline[2].rt )){	DATA_HAZARD_FLG_ONE = true;  }
		}
		
		// (b) If an instruction in EX2 is a load instruction which will write into register X while the instruction in ID is reading from X...
		if ( will_read_from_memory(4) && will_read_from_reg(2) ){
			
			if (pipeline[4].rt == pipeline[2].rt || pipeline[4].rt == pipeline[2].rs){ DATA_HAZARD_FLG_TWO = true; } // set flag		
		}
		// (c) If an instruction in MEM1 is a load instruction which will write into a register X while the instruction in ID is reading from register X..
		if ( will_read_from_memory(5) && will_read_from_reg(2) ){
			
			if (pipelin[5].rt == pipeline[2].rt || pipeline[5].r == pipeline[2].rs){ DATA_HAZARD_FLG_THREE = true; } // set flag
		}
		
	// Structural Hazards: 
		// If the instruction in WB is trying yo write into the reg. file whil the instruction at ID is trying to read from the reg. file...
		if (will_write_to_reg(7) && will_read_from_reg(2)){ STRUCTURAL_HAZARD_FLG = true; }
		
	// Control Hazards: 
		
		if (strcmp(pipelin[4].type, "BRANCH") == 0){
			
			// if prediction correct --> do nothing
			
			// if prediction is wrong:
				CONTROL_HAZARD_FLG = true;  			
		}
}

// Take neccessay action if the flag is true
void avoid_hazards(){
	
	
	if (STRUCTURAL_HAZARD_FLG == true){
		
		
	} 
	
	if (DATA_HAZARD_FLG_ONE == true){
		
		
		
	}  
	
	if(DATA_HAZARD_FLG_TWO == true){
		
		
		
	} 
	
	if (DATA_HAZARD_FLG_THREE == false){
		
		
	}
	 
 	if(CONTROL_HAZARD_FLG == true){
		
		
	}
	
}


void clear_flags(){
	
	// Reset all the flags to false..
	STRUCTURAL_HAZARD_FLG = false; 
	DATA_HAZARD_ONE = false; 
	DATA_HAZARD_TWO = false; 
	DATA_HAZARD_THREE = false; 
	CONTROL_HAZARD = false; 
}

#endif
