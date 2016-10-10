
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


void check_hazards(){
	
	
	// Data Hazards: 
		
		if (strcmp(pipeline[0].type, "")){
			
			DATA_HAZARD_FLG_ONE = true; 
			
		}else if ( (strcmp(pipelin[4].type, "LOAD") == 0) && (strcmp(pipeline[2].type, "READ") == 0) ){
			
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
		
		
	} else if (DATA_HAZARD_ONE == true){
		
		
		
	} else if(DATA_HAZARD_TWO == true){
		
		
		
	} else if (DATA_HAZARD_THREE == false){
		
		
	} else if(CONTROL_HAZARD == true){
		
		
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
