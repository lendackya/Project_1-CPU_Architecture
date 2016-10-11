
#include "PipelinedCPU.h"
#include <string.h>

#ifndef HAZARD_CONTROL
#define HAZARD_CONTROL

extern int hazard_flag;

// GLOBAL FLAGS
bool STRUCTURAL_HAZARD_FLG = false; 
bool DATA_HAZARD_FLG_ONE = false; 
bool DATA_HAZARD_FLG_TWO = false; 
bool DATA_HAZARD_FLG_THREE = false; 
bool CONTROL_HAZARD_FLG = false; 

// Checks if the instruction in the given stage is a 'Write' instruction
bool will_write_to_reg(int stage, trace_item_t pipeline[]){
	
	if (pipeline[stage].type == ti_RTYPE || pipeline[stage].type == ti_LOAD || pipeline[stage].type == ti_ITYPE){ return true; }
		
	return false; 
}

// Checks if the instuction in the given stage is a 'Read' instruction
bool will_read_from_reg(int stage, trace_item_t pipeline[]){

	if (pipeline[stage].type == ti_RTYPE || pipeline[stage].type == ti_ITYPE || pipeline[stage].type == ti_BRANCH){ return true; }
	
	return false; 
}

// Checks if the instruction in the given stage will read from memory
bool will_read_from_memory(int stage, trace_item_t pipeline[]){
	
	if (pipeline[stage].type == ti_LOAD){ return true; }
	
	return false; 	
}

// Checks if the instruction in the given stage will write to memory 
bool will_write_to_memory(int stage, trace_item_t pipeline[]){
	
	if (pipeline[stage].type == ti_STORE ){ return true; }
	
	return false; 	
}

void check_hazards(trace_item_t pipeline[]){
	
	// Data Hazards: 
		
		// (a) If an instruction in EX1 will write into a register while the instruction in ID is reading from register X, ...
		if (will_write_to_reg(3, pipeline) && will_read_from_reg(2, pipeline)){
			
			//	LOAD has Rt and Rd inverted in traces, re-routing detection
			if (pipeline[3].type == ti_LOAD) {
				if ((pipeline[3].rt != 255) && ((pipeline[3].rt == pipeline[2].rs) || (pipeline[3].rt == pipeline[2].rt )) ){	DATA_HAZARD_FLG_ONE = true;  }
			} else {
				if ((pipeline[3].rd != 255) && ((pipeline[3].rd == pipeline[2].rs) || (pipeline[3].rd == pipeline[2].rt )) ){	DATA_HAZARD_FLG_ONE = true;  }
			}
		}
		
		// (b) If an instruction in EX2 is a load instruction which will write into register X while the instruction in ID is reading from X...
		if ( will_read_from_memory(4, pipeline) && will_read_from_reg(2, pipeline) ){
			
			if (pipeline[4].type == ti_LOAD) {
				if ((pipeline[4].rd != 255) && (pipeline[4].rd == pipeline[2].rt || pipeline[4].rd == pipeline[2].rs)){ DATA_HAZARD_FLG_TWO = true; }
			} else {
				if ((pipeline[4].rt != 255) && (pipeline[4].rt == pipeline[2].rt || pipeline[4].rt == pipeline[2].rs)){ DATA_HAZARD_FLG_TWO = true; }
			}		
		}
		// (c) If an instruction in MEM1 is a load instruction which will write into a register X while the instruction in ID is reading from register X..
		if ( will_read_from_memory(5, pipeline) && will_read_from_reg(2, pipeline) ){
			
			if (pipeline[5].type == ti_LOAD) {
				if ((pipeline[5].rd != 255) && (pipeline[5].rd == pipeline[2].rt || pipeline[5].rd == pipeline[2].rs)){ DATA_HAZARD_FLG_THREE = true; }
			} else {
				if ((pipeline[5].rt != 255) && (pipeline[5].rt == pipeline[2].rt || pipeline[5].rt == pipeline[2].rs)){ DATA_HAZARD_FLG_THREE = true; }
			}			
		}
		
	// Structural Hazards: 
		// If the instruction in WB is trying yo write into the reg. file whil the instruction at ID is trying to read from the reg. file...
		if (will_write_to_reg(7, pipeline) && will_read_from_reg(2, pipeline)){ STRUCTURAL_HAZARD_FLG = true; }
		
	// Control Hazards: 
		
		if (pipeline[4].type == ti_BRANCH){
			
			// if prediction correct --> do nothing
			
			// if prediction is wrong:
				CONTROL_HAZARD_FLG = true;  			
		}
		
		
	//	assign hazard stalling based on flags & priority
	if (STRUCTURAL_HAZARD_FLG == true) {
		hazard_flag = 1;
	} else if (DATA_HAZARD_FLG_THREE == true) {
		hazard_flag = 2;
	} else if (DATA_HAZARD_FLG_TWO == true || CONTROL_HAZARD_FLG == true) {
		hazard_flag = 3;
	} else if (DATA_HAZARD_FLG_ONE == true) {
		hazard_flag = 4;
	} else {
		hazard_flag = 0;
	}
}

void print_hazards() {
	printf("Hazards: Structural=%d, Data1=%d, Data2=%d, Data3=%d, Control=%d\n", STRUCTURAL_HAZARD_FLG, DATA_HAZARD_FLG_ONE, DATA_HAZARD_FLG_TWO, DATA_HAZARD_FLG_THREE, CONTROL_HAZARD_FLG);
}

// Take neccessay action if the flag is true
void avoid_hazards(){
	
	
	if (STRUCTURAL_HAZARD_FLG == true){
		
		// Stall IF1, IF2, 
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
	DATA_HAZARD_FLG_ONE = false; 
	DATA_HAZARD_FLG_TWO = false; 
	DATA_HAZARD_FLG_THREE = false; 
	CONTROL_HAZARD_FLG = false; 
}

#endif
