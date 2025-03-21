
#ifndef TABLE_H
#define TABLE_H
#define TABLE_SIZE 23

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
void create_table(int size);
Pair *create_pair(char *key, int value);
#endif
