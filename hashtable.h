
#ifndef TABLE_H
#define TABLE_H

typedef struct Pair Pair;

struct Pair {
 char* key;
int value;
Pair *next;
}; 

typedef struct Table {
Pair **table;
int size;
} Table;

int hash( char* key);
void put( char* key, int value);
int get(char* key);
Table *createTable(int size);
Pair *createPair(char *key, int value);
#endif
