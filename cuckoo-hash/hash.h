#ifndef __HASH__
#define __HASH__

typedef struct hashtable_s 
{
  int *t1;      // table 1
  int *t2;      // table 2
  size_t size;  // tamanho das tables
} hashtable_t;

typedef struct input_s
{
  int key;      // valor a ser inserido ou removido na hashtable
  char action;  // i (INSERE); r (REMOVE); '\0' (INATIVO)
} input_t;

input_t * getInputs(size_t size);

hashtable_t initHashtable(size_t size);
void freeHashtable(hashtable_t ht);

int h1(int key, size_t size);
int h2(int key, size_t size);

int lookup(int key, hashtable_t ht);
void insert(int key, hashtable_t ht);
void delete(int key, hashtable_t ht);

void print_ht(hashtable_t ht);

#endif // __HASH__
