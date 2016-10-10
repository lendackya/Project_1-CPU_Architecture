#ifndef HASH_TABLE
#define HASH_TABLE

typedef struct hash_table{
	char* addresses[64]; // array of addresses
	int was_taken[64];	 // array that stores is the prediction was true (1) or false (0) or not touched (-1)
	int max_size; // how big the table is
	
} hash_table; 


// Inititalizes the Hash Table
void init_hash_table(hash_table* ht){
	
	ht->max_size = 64; // how many positions
	// init all the address and predicted values
	for (int i = 0; i < ht->max_size; i++){
		ht->addresses[i] = "NULL";
		ht->was_taken[i] = -1;  
	}
}

// Adds the 
void ht_add(int key, char* address, bool was_taken, hash_table* ht){
	
	// check if 0 <= key < max_size 
	if ((key >= 0) && (key < ht->max_size)){
		
		ht->addresses[key] = address; 
		ht->was_taken[key] = was_taken; 		
	}
}

// Checks the Hash Table and returns true if the postion in the index is in use, false otherwise
bool ht_contains(int key, hash_table* ht){
	

	if (ht->was_taken[key] == 0 || ht->was_taken[key] == 1){
		
		return true; 
	}else{
		
		return false; 
	}
}

// Prints the Address and branch predicted value
void ht_print(int key, hash_table* ht){ printf("Index: %d, Address: %s, Taken: %d \n", key, ht->addresses[key], ht->was_taken[key]); }


// Loop through the Hash Table and prints all the Indices that have 'true' as their predicted value
void ht_print_taken_pos(hash_table* ht){
	
	for (int i = 0; i < ht->max_size; i++){
		
		if (ht->was_taken[i] == 1 || ht->was_taken[i] == 0){
			
			ht_print(i, ht); 
		}
	}
}

// Loops through the whole table and prints the details
void ht_print_full_table(hash_table* ht){

	for (int i = 0; i < ht->max_size; i++ ){
		
		ht_print(i, ht); 		
	}
}

#endif
//EOF