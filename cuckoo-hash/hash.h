#ifndef __HASH_H__
#define __HASH_H__

#define SIZE 11
#define FREE -1     // valor inicial, espaço ainda não usado
#define DEL -2      // valor para espaço que teve chave removida

struct hashtable_s {
  int *t1; // table 1
  int *t2; // table 2
  size_t size; // tamanho das tables
};

int* initTable(size_t size);
struct hashtable_s initHashtable(size_t size);
void freeHashtable(struct hashtable_s ht);

int h1(int key, size_t size);
int h2(int key, size_t size);

void insert(int key, struct hashtable_s ht);
void delete(int key, struct hashtable_s ht);

#endif // __HASH_H__
