
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
void put( char* key, int value, Table *t);
int get(char* key, Table *t);
Table *create_table(int size);
Pair *create_pair(char *key, int value);
void destroy_table(Table* table);
#endif
