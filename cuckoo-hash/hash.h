#ifndef __HASH__
#define __HASH__

#define SIZE 11
#define FREE -1     // valor inicial, espaço ainda não usado
#define DEL -2      // valor para espaço que teve chave removida

typedef struct hashtable_s {
  int *t1; // table 1
  int *t2; // table 2
  size_t size; // tamanho das tables
} hashtable_t;

int* initTable(size_t size);
hashtable_t initHashtable(size_t size);
void freeHashtable(hashtable_t ht);

int h1(int key, size_t size);
int h2(int key, size_t size);

void insert(int key, hashtable_t ht);
void delete(int key, hashtable_t ht);

#endif // __HASH__
