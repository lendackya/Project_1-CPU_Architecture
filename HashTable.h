//
//	CoE 1541 Fall 2016 Project 1
//	8-Stage Pipelined CPU Trace-Simulator
//	by Max Garber <mbg21@pitt.edu> & Andrew Lendacky <anl119@pitt.edu>
//

#ifndef HASH_TABLE
#define HASH_TABLE

#include "CPUParameters.h"

typedef struct hash_table{
	__uint32_t addresses[HTMAXSIZE]; 	// array of addresses
	int was_taken[HTMAXSIZE];	 	// array that stores is the prediction was true (1) or false (0) or not touched (-1)
	int max_size; 					// how big the table is
	
} hash_table; 

// Inititalizes the Hash Table
void init_hash_table(hash_table* ht){
	
	ht->max_size = HTMAXSIZE; // how many positions
	// init all the address and predicted values
	for (int i = 0; i < ht->max_size; i++){
		ht->addresses[i] = 0;
		ht->was_taken[i] = -1; // -1 denotes that the positions has not been touched yet
	}
}

#ifndef PIPELINEDCPU
int is_big_endian() {
	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };
	return bint.c[0] == 1;
}
#endif

__uint32_t getBits9to4(__uint32_t data) {
	if(!is_big_endian()) {
		return ((data & 0x000003F0) >> 4);
	} else {
		return ((data & 0x0FC00000) << 4);
	}
}

// Adds the address andif it was taken (1) or not taken (0)
void ht_add(int key, __uint32_t address, int was_taken, hash_table* ht){
	if (DEBUG_BRANCHPRED) printf("ht_add(key:%d, addr:0x%X, was_taken:%d, ht)\n", key, address, was_taken);
	// check key size error
	if ((key >= 0) && (key < ht->max_size)){
		
		ht->addresses[key] = address; 
		ht->was_taken[key] = was_taken; 		
	}
}

// Checks the Hash Table and returns true (1) if the postion in the index is in use, false (0) otherwise
bool ht_contains(int key, hash_table* ht){
	
	if (ht->was_taken[key] == 0 || ht->was_taken[key] == 1){ return true; }
	else{ return false; }
}

// Prints the Address and branch predicted value
void ht_print(int key, hash_table* ht){ printf("Index: %d, Address: 0x%X, Taken: %d \n", key, ht->addresses[key], ht->was_taken[key]); }


// Loop through the Hash Table and prints all the Indices that have 'true' as their predicted value
void ht_print_tracked_pos(hash_table* ht){
	
	for (int i = 0; i < ht->max_size; i++){
		
		if (ht->was_taken[i] == 1 || ht->was_taken[i] == 0){ ht_print(i, ht); }
	}
}

// Loops through the whole table and prints the details
void ht_print_full_table(hash_table* ht){
	printf("ht_print_full_table\n");
	printf("ht->maxsize = %d\n", ht->max_size);
	for (int i = 0; i < ht->max_size; i++ ){ ht_print(i, ht); }
}

#endif
//EOF