//
//	CoE 1541 Fall 2016 Project 1
//	8-Stage Pipelined CPU Trace-Simulator
//	by Max Garber <mbg21@pitt.edu> & Andrew Lendacky <anl119@pitt.edu>
//

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "PipelinedCPU.h"
#include "HashTable.h"
#include "HazardControl.h"
#include "CPUParameters.h"
#include "branchPredictor.h"


//	Global Variables
char* trace_filename;
FILE* trace_fd;
trace_item_t* trace_buffer;
int trace_buf_ptr, trace_buf_end;
bool trace_view_on;
int branch_prediction_method;
unsigned int step;
trace_item_t pipeline[8];
hash_table ht;
int hazard_flag;
bool branch_predicted_wrong;
unsigned int last_trace_item_pc;

//	Simulation Functions
void sim_init(int argc, char *argv[]) {
	step = 0;
	branch_predicted_wrong = false;
	
	//	check for proper invocation
	if(argc == 1) {
		fprintf(stdout, "\nUSAGE: tv <trace_file> <trace_view_on> <branch_prediction_method>\n");
		//	include line about branch prediction method
		fprintf(stdout, "\n<trace_view_on> use any nonzero character to turn on or off individual item view.");
		fprintf(stdout, "\n<branch_prediction_method> use to select branch prediction method 0, 1, or 2\n\n");
		exit(0);
	}
	//	set trace filename
	trace_filename = argv[1];
	//	set trace view state
	trace_view_on = false;
	if(argc >= 3) trace_view_on = (atoi(argv[2]) != 0);
	
	branch_prediction_method = 0;
	if(argc == 4) branch_prediction_method = atoi(argv[3]);
	if( !(branch_prediction_method == 0 || branch_prediction_method == 1 || branch_prediction_method == 2) ) {
		printf("must omit entirely or enter a VALID branch prediction method\n");
		exit(0);
	}
	
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
	
	hazard_flag = 0;
	
	if (DEBUG) printf("trace_view_on = %u, branch_prediction_method=%d\n", trace_view_on, branch_prediction_method);
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
	printf("%6s (pc: 0x%0.8X) rs: %0.3d, rt: %0.3d, rd: %0.3d, addr: 0x%0.8X\n", 
		typestrings[ti->type], ti->pc, ti->rs, ti->rt, ti->rd, ti->addr);
}

void print_pipeline() {
	printf("———————————————————————————————————————————————————————————————————————————\n");
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
}

void insert_nop(int stage){
	pipeline[stage].type = ti_NOP;
	pipeline[stage].rs = 0;
	pipeline[stage].rt = 0;
	pipeline[stage].rd = 0;
	pipeline[stage].pc = 0x0;
	pipeline[stage].addr = 0x0;
}


//	Main function
int main(int argc, char *argv[]) {
	
	//	initialize the simulation
	sim_init(argc, argv);
	
	//	setup for trace file reading
	trace_item_t *tr_entry;
	size_t size;
	
	//	run
	bool pipeDraining = false;
	while(1) {
		//	diagnostics
		if (DEBUG) print_pipeline();
		
		//	run branch predictor
		branch_pred(0, pipeline, &ht);
		
		//	check for hazards - use prioritization
		check_hazards(pipeline);
		
		if (DEBUG) print_hazards();
		
		//	handle hazards (hazard_flag)
		//...
		
		if (hazard_flag == 0) {
			// no hazards, advance everything normally
			for(int i=7; i>=0; i--) {
				pipeline[i] = pipeline[i-1];
			}
			
			if (pipeDraining == false) {
				size = trace_get_item(&tr_entry);
				if(!size) {
					//	no more trace items to run through simulation 
					if (DEBUG) printf("grabbed last instruction from buffer after %u cycles, with pc: 0x%0.8X\n", step, last_trace_item_pc);
					insert_nop(0);
					pipeDraining = true;
				} else {
					//	loading the incoming trace item into the pipeline queue
					pipeline[0].type = tr_entry->type;
					pipeline[0].rs = tr_entry->rs;
					pipeline[0].rt = tr_entry->rt;
					pipeline[0].rd = tr_entry->rd;
					pipeline[0].pc = tr_entry->pc;
					pipeline[0].addr = tr_entry->addr;
					last_trace_item_pc = tr_entry->pc;
					step++;
				}
			} else {
				insert_nop(0);
				step++;
			}
		} else if (hazard_flag == 1) {
			// WB structural hazard. only WB advances everything else stalls
			if (DEBUG) printf("detected WB-structural hazard.\n");
			insert_nop(7);
			step++;
			if (DEBUG) printf("handled structural hazard at WB.\n");
			if (DEBUG) print_pipeline();
		} else if (hazard_flag == 2) {
			//	data hazard from MEM1
			if (DEBUG) printf("detected data hazard from MEM1.\n");
			//	stall ID & preceding stages, advance everything else
			for(int i=7; i>2; i--) {
				pipeline[i] = pipeline[i-1];
			}
			insert_nop(3);
			if (DEBUG) printf("handled data hazard at MEM1.\n");
			if (DEBUG) print_pipeline();
			step++;
		} else if (hazard_flag == 3) {
			// data hazard from EX2 OR control hazard from EX2
			//	need to check which
			if (pipeline[4].type == ti_BRANCH) {
				// control hazard IF we predicted wrong
				if (DEBUG) printf("detected possible control hazard from EX2.\n");
				
				if (branch_predicted_wrong) {
					// IF WE PRREDICTED WRONGLY:
						if (DEBUG) printf("branch wrongly predicted -- simulate flush via stalling.\n");
					//	stall all instructions behind the branch for four cycles to simulate flushing IF1, IF2, ID, & EX1
					for(int j=0; j<3; j++) {
						//	let everything at EX2 and beyond advance
						for(int i=7; i>3; i--) {
							pipeline[i] = pipeline[i-1];
						}
						insert_nop(4);
						step++;
						if (DEBUG) print_pipeline();
					}
					if (DEBUG) printf("handled control hazard at EX2.\n");
					if (DEBUG) print_pipeline();
				} else {
					//	if we were right, we just let everything advance one like hazard_flag = 0
					if (DEBUG) printf("branch predicted correctly, no invervention needed.\n");
					// no hazards, advance everything normally
					for(int i=7; i>=0; i--) {
						pipeline[i] = pipeline[i-1];
					}
					if (pipeDraining == false) {
						size = trace_get_item(&tr_entry);
						if(!size) {
							//	no more trace items to run through simulation 
							if (DEBUG) printf("grabbed last instruction from buffer after %u cycles, with pc: 0x%0.8X\n", step, last_trace_item_pc);
							insert_nop(0);
							pipeDraining = true;
						} else {
							//	loading the incoming trace item into the pipeline queue
							pipeline[0].type = tr_entry->type;
							pipeline[0].rs = tr_entry->rs;
							pipeline[0].rt = tr_entry->rt;
							pipeline[0].rd = tr_entry->rd;
							pipeline[0].pc = tr_entry->pc;
							pipeline[0].addr = tr_entry->addr;
							last_trace_item_pc = tr_entry->pc;
							step++;
						}
					} else {
						insert_nop(0);
						step++;
					}
				}
			} else {
				if (DEBUG) printf("detected data hazard from EX2.\n");
				//	stall ID & preceding stages, advance everything else
				for(int i=7; i>2; i--) {
					pipeline[i] = pipeline[i-1];
				}
				insert_nop(3);
				if (DEBUG) printf("handled data hazard at EX2.\n");
				if (DEBUG) print_pipeline();
				step++;
			}
			step++;
		} else if (hazard_flag == 4) {
			// data hazard from EX1. 
			if (DEBUG) printf("detected data hazard from EX1.\n");
			//	stall ID & preceding stages, advance everthing else
			for(int i=7; i>2; i--) {
				pipeline[i] = pipeline[i-1];
			}
			insert_nop(3);
			if (DEBUG) printf("handled data hazard at EX1.\n");
			if (DEBUG) print_pipeline();
			step++;
		} else {
			printf("grave hazard detection error.\n");
			break;
		}
		
		if(pipeDraining == true && (pipeline[7].pc == last_trace_item_pc)) {
			// our last trace item is in the last stage of the pipeline;
			step++;
			if (DEBUG) printf("last trace item reached last stage of pipeline.\n");
			if (DEBUG) print_pipeline();
			
			insert_nop(7);
			step++;
			if (DEBUG) print_pipeline();
			printf("last trace item executed after %u steps\n", step);
			break;
		}
		
		if (trace_view_on == true) {
			printf("Cycle %u : ", step);
			print_trace_item(&(pipeline[7]));
			
		}

		//	clear flags
		clear_flags();
		
		//	limit test runs for now
		if(step >= STEPLIMIT) break;
	}//end-while
	
	//	cleanup
	sim_uninit();
	return 0;
}