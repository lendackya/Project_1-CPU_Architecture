#include "PipelinedCPU.h"
#include "HashTable.h"

#ifndef BRANCH_PREDICTOR
#define BRANCH_PREDICTOR

// Checks the IF1 stage, and gets the type of instruction 
char* get_instruction_type(trace_item_t* pipeline[]){
	
	// Check IF1 for to see if we have a branch instruction
	return = typestrings[pipeline[0].type];
}

bool evaluate_branch_cond(trace_item_t* pipeline[]){
	
	return true; 
}

void branch_pred(int prediction_method, trace_item_t* pipline[]){
	
	
	// Check if we have to branch
	char* instn_type = get_instruction_type(pipeline); 
	bool branch_b = evalulate_branch_cond(pipeline);
	
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
			
			// Check the hash map 			
			// Prediction: Taken (1)
			if (ht.wasTaken[decimal] == true){
				
				// get the target address and set PC to it
				// flush previous instructions by inserting NOPs
				for (int i = 0; i < 4; i++){
					
					insert_no_op(i, pipeline);
				}
				
				// Taken:
					// Do nothing, we're already set up to handle this.
				
				// Not Taken:
					// revert back to old PC
					// DO NOT flush instructions
				
			}
			// Prediction: Not Taken (0)
			else if (ht.wasTaken[decimal] == false){
						
				// Taken:
					// Jump to target address and flush previous instructions (4 instructions)
					for (int i = 0; i < 4; i++){
						
						insert_no_op(i, pipeline);
					}
					
				// Not Taken: 
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
