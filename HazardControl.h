
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
		
		if (will_write_to_reg(0) && will_read_from_reg(2)){
			
			if (pipeline[0].rd == pipelin[2].rd){
				DATA_HAZARD_FLG_ONE = true; 
			}
			
		}else if ( pipeline[4].type == ti_LOAD && (strcmp(pipeline[2].type, "READ") == 0) ){
			
			if (pipeline[4].rt == pipeline[0].rt ){ DATA_HAZARD_FLG_TWO = true; } // set flag
			
		}else if ( (strcmp(pipeline[5].type , "LOAD") == 0) && (strcmp(pipeline[2].type, "READ") == 0) ){
			
			if (pipelin[5].rt == pipeline[2].rt){ DATA_HAZARD_FLG_THREE = true; } // set flag
		}
		
	// Structural Hazards: 
		
		if (pipeline[7]){
			
			STRUCTURAL_HAZARD_FLG = true; 
		}
		
		
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
