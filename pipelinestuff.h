#ifndef PIPELINESTUFF
#define PIPELINESTUFF

#define TRACE_BUFFERSIZE 1024*1024

//	Structures
enum instruction_t {
	ti_NOP = 0,
	ti_RTYPE,
	ti_ITYPE,
	ti_LOAD,
	ti_STORE,
	ti_BRANCH,
	ti_JTYPE,
	ti_SPECIAL,
	ti_JRTYPE
};

typedef struct trace_item_t {
	unsigned char type;			// see above
	unsigned char rs;		// 1st operand
	unsigned char rt;		// 2nd operand
	unsigned char rd;			// dest. operand
	unsigned int pc;			// program counter
	unsigned int addr;			// mem. address
} trace_item_t;


// Runtime/Global Variables
char* trace_filename;
bool trace_view_on;
FILE *trace_fd;
trace_item_t *trace_buffer;
int trace_buf_ptr, trace_buf_end;

trace_item_t pipeline[8];


// Global Functions
void simulation_init(int argc, char *argv[]) {
	//	check proper invocation
	if(argc == 1) {
		fprintf(stdout, "\nUSAGE: tv <trace_file> <switch - any character>\n");
		//	include line about branch prediction method
		fprintf(stdout, "\n(switch) to turn on or off individual item view.\n\n");
		exit(0);
	}
	
	//	grab filename
	trace_filename = argv[1];
	
	//	set trace view
	trace_view_on = false;
	if(argc == 3) trace_view_on = (atoi(argv[2]) == 0);
	
	//	set branch prediction method
	//	TBImplemented
	
	//	open the file
	fprintf(stdout, "\n ** opening file %s\n", trace_filename);
	trace_fd = fopen(trace_filename, "rb");
	//	error check -- if the file can't be opened, die
	if (!trace_fd) {
		fprintf(stdout, "\ntrace file %s not opened.\n\n", trace_filename);
		exit(0);
	}
	
	//	read in the trace file in its entirety to the buffer
	trace_buffer = malloc(sizeof(trace_item_t) * TRACE_BUFFERSIZE);
	//	error check -- if we can't allocate the buffer, die
	if (!trace_buffer) {
		fprintf(stdout, "** trace_buf not allocated\n");
		exit(-1);
	}
	trace_buf_ptr = 0;
	trace_buf_end = 0;

}

void simulation_uninit() {
	free(trace_buffer);
	fclose(trace_fd);
}

#endif
//EOF
