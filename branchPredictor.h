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
bool was_branch_taken(trace_item_t* pipeline[]){
	
	// We did take a branch..
	if (pipeline[4].pc != (pipeline[3].pc + 4)){ return true; }
	else{ return false; }
}


// Predicts the Branch Instruction and takes the correct action
void branch_pred(int prediction_method, trace_item_t* pipline[]){
	
	
	// Check if we have to branch
	char* instn_type = get_instruction_type(pipeline); 
	bool branch_cond = evalulate_branch_cond(pipeline);
	
	// Predict 'Not Taken'
	if (prediction_method == 0){
				
		if ( (strcmp(condition_str, "BRANCH") == 0) && (was_branch_taken(pipeline) == true) ){
		
			// stall previous stages by inserting NOPs
		
//			for (int i = 0; i < 4; i++){
//				
//				insert_no_op(i, pipeline);
//			}
//			//print_pipeline();
		}
	}
	// 1 bit Branch Predictor
	else if (prediction_method == 1){
				
		//if ( (strcmp(condition_str, "BRANCH") == 0) && (was_branch_taken(pipeline) == true) ){
			
			// get bits 9-4 of instruction
			u_int32_t bits = getBits9to4(pipeline[4].pc)
		
			// convert bits to int, 0-63
			bool pred_valid; 
			// Prediction: Taken (1)
			if (ht.was_taken[(int) bits] == 1){
				
				// Taken ---> Jump to the Target Address and start grabbing instructions from that address.
				
				pred_valid = pipeline[4].pc != (pipeline[3].pc + 4); 
				// get the target address and set PC to it

				// If prediction was correct --> Do nothing. We're already set up to handle this.
					
				// If we find our prediction was wrong..
				if (branch_cond == false){
					// Not Taken:
						// revert back to old PC
						// DO NOT flush instructions
				}
			}
			// Prediction: Not Taken (0)
			else if (ht.was_taken[(int) bits] == 0){
						
				// Not Taken ---> Continue to pull instrcutions from Instruction Memory as we normally would.
				pred_valid = pipleline[4].pc == (pipeline[3].pc + 4);				
				// If we find out prediction is wrong and we need to take the branch...
				// Jump to the Target Address and flush the previous stages
					
				// If our prediction is correct.. 
				// Do nothing, we're already set up to handle this. 	
			}
			// nothing is in that slot yet, i.e, hash_table[decimal].address == NULL && hash_table[decimal].was_taken == -1 
			else if (ht_contains((int) bits, &ht) == false){
					
				// we predict not taken
				pred_valid = pipleline[4].pc == (pipeline[3].pc + 4);	
			}
				
			if (pred_valid == false){
				
				// update the hash table
				bool taken = (pipeline[4].pc != (pipeline[3].pc + 4));
				ht_add((int) bits, pipeline[4].pc, taken, &ht)
			}
		}
	//}
	// 2 Bit Branch Predictor
	else if (prediction_method == 2){
		
	}
	
}

#endif
//EOF
