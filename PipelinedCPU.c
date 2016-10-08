//
//	CoE 1541 Fall 2016 Project 1
//	8-Stage Pipelined CPU Trace-Simulator
//	by Max Garber <mbg21@pitt.edu> & Andrew Lendacky <anl119@pitt.edu>
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "PipelinedCPU.h"


//	Global Variables
char* trace_filename;
FILE* trace_fd;
trace_item_t* trace_buffer;
int trace_buf_ptr, trace_buf_end;
bool trace_view_on;
unsigned int step;
trace_item_t pipeline[8];


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
	fprintf(stdout, "\n ** opening file %s\n", trace_filename);
	trace_fd = fopen(trace_filename, "rb");
	//	error check -- if the file can't be opened, die
	if (!trace_fd) {
		fprintf(stdout, "\ntrace file %s not opened.\n\n", trace_filename);
		exit(0);
	}
	//	set up the trace file buffer
	trace_buffer = malloc(sizeof(trace_item_t) * TRACE_BUFFERSIZE);
	//	error check -- if we can't allocate the buffer, die
	if (!trace_buffer) {
		fprintf(stdout, "** trace_buf not allocated\n");
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
		if (!n_items) return 0;				/* if no more items in the file, we are done */
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
	printf("%s rs: %d\n", typestrings[ti->type], ti->rs);
}

void print_pipeline() {
	printf(" ——————STEP: %d\n", step);
	printf(" IF1 | ");
	print_trace_item(&(pipeline[0]));
	printf(" IF2 | ");
	print_trace_item(&(pipeline[1]));
	printf("  ID | ");
	print_trace_item(&(pipeline[2]));
	printf(" EX1 | ");
	print_trace_item(&(pipeline[3]));
	printf(" EX2 | ");
	print_trace_item(&(pipeline[4]));
	printf("MEM1 | ");
	print_trace_item(&(pipeline[5]));
	printf("MEM2 | ");
	print_trace_item(&(pipeline[6]));
	printf("  WB | ");
	print_trace_item(&(pipeline[7]));
	printf("\n");
}


//	Main function
int main(int argc, char *argv[]) {
	
	//	initialize the simulation
	sim_init(argc, argv);
	
	//	setup for trace file reading
	trace_item_t *tr_entry;
	size_t size;
	unsigned int n_cycle = 0;
	
	
	size = trace_get_item(&tr_entry);
	if(!size) {
		printf("Completed loading trace file instructions -- drain the pipeline\n");
	}
	
	
	
	//	Begin the processor!
	
	//	fetch	
	pipeline[0] = *(tr_entry);
	
	//status
	print_pipeline();
	
	
	
	
	//	cleanup
	sim_uninit();
	return 0;
}