#include "PipelinedCPU.h"
#include "HashTable.h"

#ifndef BRANCH_PREDICTOR
#define BRANCH_PREDICTOR

void branch_pred(int prediction_method, trace_item_t* pipline[]){
	
	// Check IF1 for to see if we have a branch instruction
	char* condition_str = typestrings[pipeline[0].type];
	
	// Check if we have to branch
	bool branch_b = true;
	
	// Predict 'Not Taken'
	if (prediction_method == 0){
				
		if (strcmp(condition_str, "BRANCH") == 0 && branch_b == true){
		
			// stall previous stages by insertin NOPs
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
		
			// convert bits to int, 0-64
			
			// Check the hash map 
			
			// prediction: true
			if (ht.wasTaken[decimal] == true){
				
				
			}
			// prediction: false 
			else if (ht.wasTaken[decimal] == false){
				
				
			}
			// nothing is in that slot yet
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
