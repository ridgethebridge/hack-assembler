#include<stdio.h>
#include "hashtable.h"
#include<string.h>
#include<stdlib.h>

Table *hTable;

int hash( char* key) {
int result = 0;
while(*key) {
result+=*key++;
}
return result;
}

void put(char* key, int value) {
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

int get( char* key) {
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

void create_table(int size) {
hTable = malloc(sizeof(Table));
hTable->size = size;
hTable->table = calloc(size,sizeof(Pair*)); //sets pointers to actual pairs to null
}

