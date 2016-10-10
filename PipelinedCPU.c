//
//	CoE 1541 Fall 2016 Project 1
//	8-Stage Pipelined CPU Trace-Simulator
//	by Max Garber <mbg21@pitt.edu> & Andrew Lendacky <anl119@pitt.edu>
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "HashTable.h"
#include "PipelinedCPU.h"


//	Global Variables
char* trace_filename;
FILE* trace_fd;
trace_item_t* trace_buffer;
int trace_buf_ptr, trace_buf_end;
bool trace_view_on;
unsigned int step;
trace_item_t pipeline[8];

hash_table ht;

//	Simulation Functions
void sim_init(int argc, char *argv[]) {
	step = 0;
	
	//	check for proper invocation
	if(argc == 1) {
		fprintf(stdout, "\nUSAGE: tv <trace_file> <switch - any character>\n");
		//	include line about branch prediction method
		fprintf(stdout, "\n(switch) to turn on or off individual item view.\n\n");
		exit(0);
	}
	//	set trace filename
	trace_filename = argv[1];
	//	set trace view state
	trace_view_on = false;
	if(argc == 3) trace_view_on = (atoi(argv[2]) == 0);
	
	//	set branch prediction method
	//	TBImplemented
	
	//	open the trace file
	fprintf(stdout, "Opening trace file: %s\n", trace_filename);
	trace_fd = fopen(trace_filename, "rb");
	//	error check -- if the file can't be opened, die
	if (!trace_fd) {
		fprintf(stdout, "Trace file %s could not be opened.\n", trace_filename);
		exit(0);
	}
	//	set up the trace file buffer
	trace_buffer = malloc(sizeof(trace_item_t) * TRACE_BUFFERSIZE);
	//	error check -- if we can't allocate the buffer, die
	if (!trace_buffer) {
		fprintf(stdout, "Trace file buffer could not be allocated\n");
		exit(-1);
	}
	trace_buf_ptr = 0;
	trace_buf_end = 0;
}

void sim_uninit() {
	free(trace_buffer);
	fclose(trace_fd);
}

//	workhorse for trace reading -- need to understand better
int trace_get_item(trace_item_t **item) {
	int n_items;
	if (trace_buf_ptr == trace_buf_end) {	/* if no more unprocessed items in the trace buffer, get new data  */
		n_items = fread(trace_buffer, sizeof(trace_item_t), TRACE_BUFFERSIZE, trace_fd);
		if (!n_items) return 0;			/* if no more items in the file, we are done */
		trace_buf_ptr = 0;
		trace_buf_end = n_items;			/* n_items were read and placed in trace buffer */
	}

	*item = &trace_buffer[trace_buf_ptr];	/* read a new trace item for processing */
	trace_buf_ptr++;
	if (is_big_endian()) {
		(*item)->pc = my_ntohl((*item)->pc);
		(*item)->addr = my_ntohl((*item)->addr);
	}
	return 1;
}

//	Printout/Debug functions
void print_trace_item(trace_item_t* ti) {
	printf("%s (pc: 0x%0.8X) rs: %0.3d, rt: %0.3d, rd: %0.3d, addr: 0x%0.8X\n", 
		typestrings[ti->type], ti->pc, ti->rs, ti->rt, ti->rd, ti->addr);
}

void print_pipeline() {
	printf("STEP: %d\n", step);
	printf("   IF1 | ");
	print_trace_item(&(pipeline[0]));
	printf("   IF2 | ");
	print_trace_item(&(pipeline[1]));
	printf("    ID | ");
	print_trace_item(&(pipeline[2]));
	printf("   EX1 | ");
	print_trace_item(&(pipeline[3]));
	printf("   EX2 | ");
	print_trace_item(&(pipeline[4]));
	printf("  MEM1 | ");
	print_trace_item(&(pipeline[5]));
	printf("  MEM2 | ");
	print_trace_item(&(pipeline[6]));
	printf("    WB | ");
	print_trace_item(&(pipeline[7]));
	printf("—————————————————————————————————————————————————————————————————————————––\n");
}

void branch_pred(int prediction_method){
	
	// Check IF1 for to see if we have a branch instruction
	char* condition_str = typestrings[pipeline[0].type];
	
	// Check if we have to branch
	bool branch_b = true;
	
	// Not Taken
	if (prediction_method == 0){
				
		if (strcmp(condition_str, "BRANCH") == 0 && branch_b == true){
			
			printf("Branch! \n");
			// stall previous stages by insertin NOPs
			for (int i = 0; i < 4; i++){
				
				insert_no_op(i, pipeline);
			}
			print_pipeline();
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
				
				// add to the hash map	
				printf("Adding to the hash map \n"); 
				
			}
		}

		
		
	}
	// 2 Bit Branch Predictor
	else if (prediction_method == 2){
		
		
	}
	
}


//	Main function
int main(int argc, char *argv[]) {
	
	//	initialize the simulation
	sim_init(argc, argv);
	
	//	setup for trace file reading
	trace_item_t *tr_entry;
	size_t size;
	
	//	prime the pipe
	bool escapeToPipeDraining = false;
	while(1) {
		//	advance each stage's instruction
		for(int i=7; i>=0; i--) {
			pipeline[i] = pipeline[i-1];
		}
		//	need to intervene for hazards, forwarding, branch prediction, &c.
	
		size = trace_get_item(&tr_entry);
		if(!size) {
			//	no more trace items to run through simulation 
			printf("grabbed last instruction from buffer after %u cycles\n", step);
			break;
		} else {
			//	loading the incoming trace item into the pipeline queue
			pipeline[0].type = tr_entry->type;
			pipeline[0].rs = tr_entry->rs;
			pipeline[0].rt = tr_entry->rt;
			pipeline[0].rd = tr_entry->rd;
			pipeline[0].pc = tr_entry->pc;
			pipeline[0].addr = tr_entry->addr;
			step++;
		}
		//	for diagnostics for now
		// print_pipeline();
		
		 branch_pred(0); 
		//	limit test runs for now
		if(step >= STEPLIMIT) break;
	}//end-while
	
	//	now drain the pipeline and track it
	
	
	
	//	cleanup
	sim_uninit();
	return 0;
}