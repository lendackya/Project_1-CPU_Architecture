#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "HashTable.h"

int main(int argc, char *argv[]){
	
	hash_table ht; 
	
	init_hash_table(&ht); 
	
	ht_add(0, "2048283", 1, &ht); 
	ht_add(2, "484848", 1, &ht); 
	ht_add(60, "4847844", 1, &ht);
	ht_add(1, "4847844", 0, &ht);  
	
	//ht_print_full_table(&ht);
	//ht_print_taken_pos(&ht); 
	
	printf("%d \n", ht_contains(0, &ht)); 
}