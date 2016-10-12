#include "PipelinedCPU.h"
#include "HashTable.h"
#include "CPUParameters.h"

#ifndef BRANCH_PREDICTOR
#define BRANCH_PREDICTOR

extern bool branch_predicted_wrong;

// Checks the IF1 stage, and gets the type of instruction,
// i.e., "NOP", " RTYPE", " ITYPE", "  LOAD", " STORE", "BRANCH", " JTYPE", "SPECIAL", "JRTYPE"
// We only really care if the type is a BRANCH instruction..
char* get_instruction_type(trace_item_t pipeline[]){
	
	// Check IF1 for to see if we have a branch instruction
	return typestrings[pipeline[0].type];
}


// Predicts the Branch Instruction and takes the correct action
void branch_pred(int prediction_method, trace_item_t pipeline[], hash_table* ht){
	
	
	// Check if we have to branch
	char* instn_type = get_instruction_type(pipeline); 
	
	// Predict 'Not Taken'
	if (prediction_method == 0){
		// we predict not taken, i.e. pipeline[4].pc = pipeline[3].pc + 4
		branch_predicted_wrong = (pipeline[4].pc != (pipeline[3].pc + 4));
	}
	// 1 bit Branch Predictor
	else if (prediction_method == 1){
		// get bits 9-4 of instruction
		u_int32_t bits = getBits9to4(pipeline[4].pc);
	
		// convert bits to int, 0-63
		bool pred_valid; 
		// Prediction: Taken (1)
		if (ht->was_taken[(int) bits] == 1){
			
			// Taken ---> Jump to the Target Address and start grabbing instructions from that address.
			
			pred_valid = pipeline[4].pc != (pipeline[3].pc + 4); 
			// get the target address and set PC to it

			// If prediction was correct --> Do nothing. We're already set up to handle this.
		}
		// Prediction: Not Taken (0)
		else if (ht->was_taken[(int) bits] == 0){
					
			// Not Taken ---> Continue to pull instrcutions from Instruction Memory as we normally would.
			pred_valid = pipeline[4].pc == (pipeline[3].pc + 4);				
			// If we find out prediction is wrong and we need to take the branch...
			// Jump to the Target Address and flush the previous stages
				
			// If our prediction is correct.. 
			// Do nothing, we're already set up to handle this. 	
		}
		// nothing is in that slot yet, i.e, hash_table[decimal].address == 0 && hash_table[decimal].was_taken == -1 
		else if (ht_contains((int) bits, ht) == false){
				
			// we predict not taken
			pred_valid = pipeline[4].pc == (pipeline[3].pc + 4);	
		}
			
		if (pred_valid == false){
			
			// update the hash table
			bool taken = (pipeline[4].pc != (pipeline[3].pc + 4));
			ht_add((int) bits, pipeline[4].pc, taken, ht);
		}
	}
	else if (prediction_method == 2){
		
		//	prediction-int encoding:
		//	-1: no previous encounter; predict not taken by default
		//	10: not taken x2
		//	11: not taken, then taken
		//	12: taken, then not taken
		//	13: taken x2
		
		u_int32_t bits = getBits9to4(pipeline[4].pc);
		
		bool predicting_taken;						//	current prediction
		bool pred_valid;   							//	validity of current prediction
		int ht_pred = ht->was_taken[(int) bits];	//	prediction int from hashtable
		int new_ht_pred;							//	value to put in hashtable for next prediction
		
		//	determine prediction based on hashtable
		if (ht_pred == -1 || ht_pred == 10 || ht_pred == 11) {
			predicting_taken = false;
		} else if (ht_pred == 12 || ht_pred == 13) {
			predicting_taken = true;
		} else {
			predicting_taken = false;
		}
		
		//	determine if it was valid
		pred_valid = (predicting_taken) && (pipeline[4].pc != (pipeline[3].pc + 4));
		
		//	determine new hashtable prediction int value
		if (ht_pred == -1 || ht_pred == 10){
			new_ht_pred = pred_valid ? 10 : 11;
		} else if (ht_pred == 11) {
			new_ht_pred = pred_valid ? 10 : 13;
		} else if (ht_pred) {
			new_ht_pred = pred_valid ? 13 : 10;
		} else if (ht_pred) {
			new_ht_pred = pred_valid ? 13 : 12;
		} else {
			new_ht_pred = 10;
		}
		
		//	update hashtable
		ht_add((int) bits, pipeline[4].pc, new_ht_pred, ht);
	}
	
}

#endif
//EOF
