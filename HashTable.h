

typedef struct hash_table{
	char* addresses[64]; 
	bool wasTaken[64];
	int size; 
} hash_table; 


void add(int key, char* address, bool was_taken, hash_table* ht){
	
	ht->addresses[key] = address; 
	ht->wasTaken[key] = was_taken; 
	
	ht->size++; 	
}

void print_hash_table(hash_table ht){
	
	
	for (int i = 0; i < ht.size; i++ ){
		
		printf("Address: %s, Taken: %c \n", ht.addresses[i], ht.wasTaken[i]);
		
	}
}

void find(int key, hash_table ht){
	
	printf("Address: %s, Taken: %c \n", ht.addresses[key], ht.wasTaken[key]); 
	
}