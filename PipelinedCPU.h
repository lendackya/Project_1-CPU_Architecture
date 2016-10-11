//
//	CoE 1541 Fall 2016 Project 1
//	8-Stage Pipelined CPU Trace-Simulator
//	by Max Garber <mbg21@pitt.edu> & Andrew Lendacky <anl119@pitt.edu>
//

#ifndef PIPELINEDCPU
#define PIPELINEDCPU

#define TRACE_BUFFERSIZE 1024*1024
#define STEPLIMIT 128

//	Types & Structures
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

//	reference instruction type strings, with whitespace to force R-alignment on printout
char* typestrings[] = {"NOP", "RTYPE", "ITYPE", "LOAD", "STORE", "BRANCH", "JTYPE", "SPECIAL", "JRTYPE"};

typedef struct trace_item_t {
	unsigned char type;			// see above
	unsigned char rs;				// 1st operand
	unsigned char rt;				// 2nd operand
	unsigned char rd;				// dest. operand
	unsigned int pc;				// program counter
	unsigned int addr;			// mem. address
} trace_item_t;

//	Utility functions
int is_big_endian() {
	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };
	return bint.c[0] == 1;
}

void insert_no_op(int stage, trace_item_t pipeline[]){
	
	pipeline[stage].type = ti_NOP;
	pipeline[stage].rs = 0x00;
	pipeline[stage].rt = 0x00;
	pipeline[stage].rd = 0x00;
	pipeline[stage].pc = 0x00;
	pipeline[stage].addr = 0x00;
}

uint32_t my_ntohl(uint32_t x) {
	u_int8_t *s = (u_int8_t *)&x;
	return (uint32_t)(s[3] << 24 | s[2] << 16 | s[1] << 8 | s[0]);
}

#endif
//EOF
