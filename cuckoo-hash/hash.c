#include <stdio.h>
#include <stdlib.h>
#include <math.h> // para floor()
#include <assert.h>

#include "hash.h"


int* 
initTable(size_t size) 
{
    int *new_t = malloc(size * sizeof(int));
    assert(NULL != new_t);
    
    for (size_t i = 0; i < size; ++i) {
        new_t[i] = FREE;  // posição livre
    }

    return new_t;
}

struct hashtable_s
initHashtable(size_t size)
{
    struct hashtable_s new_ht = {
        .t1 = initTable(size),
        .t2 = initTable(size),
        .size = size 
    };

    return new_ht;
}

void
freeHashtable(struct hashtable_s ht)
{
  if (ht.t1)
      free(ht.t1);
  if (ht.t2)
      free(ht.t2);
}

int 
h1(int key, size_t size) {
    return key % size;
}

int 
h2(int key, size_t size) {
    return (floor(size * ((key * 0.9) - floor(key * 0.9))));
}

/* 
    a inserção é sempre na t1.
    primeiro checa se a posição h1(key) esta disponivel na t1,
    se estiver insere, se não, houve uma colisão,
    então insere o valor que ta na posição h1(key) de t1
    na posição h2(t1[h1]) na t2,
    e depois insere key em t1[h1(key)] 
*/
void 
insert(int key, struct hashtable_s ht) 
{
    int pos1 = h1(key, ht.size);
    
    // inserção na t1
    if (ht.t1[pos1] == -1 || ht.t1[pos1] == -2) {
        ht.t1[pos1] = key;
    }
    else if (h1(ht.t1[pos1], ht.size) == pos1) {    // colisão em T1
        int temp = ht.t1[pos1];
        
        if (key == ht.t1[pos1]) {      // se chave nova e antiga sao iguais ignora
            return;
        } else {                    // inserção na t2
            ht.t1[pos1] = key;
            ht.t2[h2(temp, ht.size)] = temp;
        }
    }
}

void 
delete(int key, struct hashtable_s ht) 
{
    int pos1 = h1(key, ht.size);
    int pos2 = h2(key, ht.size);

    if (ht.t1[pos1] == key) {          // confere se o valor ta na t1
        ht.t1[pos1] = DEL;
    }
    else if (ht.t1[pos1] != FREE) {
        if (ht.t2[pos2] == key)        // confere se o valor ta na t2
            ht.t2[pos2] = DEL;
    }
}
