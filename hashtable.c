#include<stdio.h>
#include "hashtable.h"
#include<string.h>
#include<stdlib.h>

int hash( char* key) {
int result = 0;
while(*key) {
result+=*key++;
}
return result;
}

void put(char* key, int value,Table*hTable) {
	int index = hash(key)%hTable->size;
	Pair *pair = *(hTable->table+index);
	while(pair) {
		if(strcmp(pair->key,key) == 0) {
			pair->value = value;
			return;
		}
		pair = pair->next;
	}
	Pair *newPair  = create_pair(key,value);
	newPair->next = *(hTable->table+index);
	(hTable->table)[index] = newPair;
}

Pair *create_pair(char *key, int value) {
	Pair *pair = malloc(sizeof(Pair));
	pair->key = calloc(25,sizeof(char));
	strcpy(pair->key,key);
	pair->value = value;
	pair->next = 0;
	return pair;
}

int get( char* key,Table *hTable) {
	int index = hash(key)%hTable->size;
	Pair *pair = *(hTable->table+index);
	while(pair) {
	if(strcmp(key,pair->key) == 0) {
		return pair->value;
		}
		pair = pair->next;
		}
	return -1;
	}

Table* create_table(int size) {
	Table *hTable = malloc(sizeof(Table));
	hTable->size = size;
	hTable->table = calloc(size,sizeof(Pair*)); 
	return hTable;
}

// removes all the tables memory, unusable after until set with create_table again
void destroy_table(Table* table) {
	for(int i = 0; i < table->size; ++i) {
		Pair *p1 = table->table[i];
		Pair *p2 = p1;
		while(p2) {
		p2 = p2->next;
		free(p1);
		p1 = p2;
		}
	}
	free(table->table);
	free(table);
}
	

	

