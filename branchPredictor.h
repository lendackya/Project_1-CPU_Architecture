#include "PipelinedCPU.h"
#include "HashTable.h"

#ifndef BRANCH_PREDICTOR
#define BRANCH_PREDICTOR

// Checks the IF1 stage, and gets the type of instruction,
// i.e., "NOP", " RTYPE", " ITYPE", "  LOAD", " STORE", "BRANCH", " JTYPE", "SPECIAL", "JRTYPE"
// We only really care if the type is a BRANCH instruction..
char* get_instruction_type(trace_item_t* pipeline[]){
	
	// Check IF1 for to see if we have a branch instruction
	return = typestrings[pipeline[0].type];
}

// Evaluates the Branch Condition and returns true if the condition is true, 
// and false if the condition is false.
bool evaluate_branch_cond(trace_item_t* pipeline[]){
	
	return true; 
}

// Predicts the Branch Instruction and takes the correct action
void branch_pred(int prediction_method, trace_item_t* pipline[]){
	
	
	// Check if we have to branch
	char* instn_type = get_instruction_type(pipeline); 
	bool branch_cond = evalulate_branch_cond(pipeline);
	
	// Predict 'Not Taken'
	if (prediction_method == 0){
				
		if (strcmp(condition_str, "BRANCH") == 0 && branch_b == true){
		
			// stall previous stages by inserting NOPs
			for (int i = 0; i < 4; i++){
				
				insert_no_op(i, pipeline);
			}
			//print_pipeline();
		}
	}
	// 1 bit Branch Predictor
	else if (prediction_method == 1){
				
		int decimal; 
				
		if (strcmp(condition_str, "BRANCH") == 0 && branch_b == true){
			
			// get bits 9-4 of instruction
		
			// convert bits to int, 0-63
					
			// Prediction: Taken (1)
			if (ht.was_taken[decimal] == true){
				
				// Taken ---> Jump to the Target Address and start grabbing instructions from that address.
				
				// get the target address and set PC to it
				// flush previous instructions by inserting NOPs
				for (int i = 0; i < 4; i++){
					
					insert_no_op(i, pipeline); 
				}
				
				// If prediction was correct --> Do nothing. We're already set up to handle this.
					
				// If we find our prediction was wrong..
				if (branch_cond == false){
					// Not Taken:
						// revert back to old PC
						// DO NOT flush instructions
				}
			}
			// Prediction: Not Taken (0)
			else if (ht.was_taken[decimal] == false){
						
				// Not Taken ---> Continue to pull instrcutions from Instruction Memory as we normally would.
									
				// If we find out prediction is wrong and we need to take the branch...
				// Jump to the Target Address and flush the previous stages
				if (branch_cond == true){
					// Jump to target address and flush previous instructions (4 instructions)
					for (int i = 0; i < 4; i++){ insert_no_op(i, pipeline); }
				}
					
				// If our prediction is correct.. 
				// Do nothing, we're already set up to handle this. 	
			}
			// nothing is in that slot yet, i.e, hash_table[decimal].address == NULL && hash_table[decimal].was_taken == -1 
			else{
								
			}
		}
	}
	// 2 Bit Branch Predictor
	else if (prediction_method == 2){
		
	}
	
}

#endif
//EOF
