#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // para strchr()
#include <math.h>       // para floor()
#include <assert.h>

#include "hash.h"

#define FREE -1 // valor inicial, espaço ainda não usado
#define DEL -2  // valor para espaço que teve chave removida


/* deserialização do conteúdo dos arquivos de entrada para um array de
 *  struct input_s contendo chaves e instruções */
input_t *
getInputs(size_t size)
{
    input_t *inputs = calloc(1, size * sizeof(input_t));
    if (NULL == inputs)
        return NULL;

    char line[256]; // tamanho mais que o suficiente
    for (size_t i = 0; i < size; ++i)
    {
        if (NULL == fgets(line, sizeof(line) - 1, stdin)) // obtem linha atual da entrada
            break;                                        // BREAK ANTECIPADO (não há mais linhas a serem lidas)

        inputs[i].action = line[0]; // ação é o primeiro char da linha

        char *strkey = 1 + strchr(line, ' ');          // obtem posicao do key no string
        inputs[i].key = (int)strtol(strkey, NULL, 10); // converte key do input para int
    }

    return inputs;
}

static int* 
initTable(size_t size) 
{
    int *new_t = malloc(size * sizeof(int));
    assert(NULL != new_t);
    
    for (size_t i = 0; i < size; ++i) {
        new_t[i] = FREE; // posição livre
    }

    return new_t;
}

hashtable_t
initHashtable(size_t size)
{
    hashtable_t new_ht = {
        .t1 = initTable(size),
        .t2 = initTable(size),
        .size = size 
    };

    return new_ht;
}

void
freeHashtable(hashtable_t ht)
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
    return floor(size * ((key * 0.9) - floor(key * 0.9)));
}

void 
insert(int key, hashtable_t ht) 
{
    int pos1 = h1(key, ht.size);
    
    // inserção na t1
    if (ht.t1[pos1] == FREE || ht.t1[pos1] == DEL) {
        ht.t1[pos1] = key;
        return; /* RETORNO ANTECIPADO */
    }

    if (pos1 == h1(ht.t1[pos1], ht.size)) { // colisão em T1
        if (key == ht.t1[pos1])
            return; /* RETORNO ANTECIPADO (chave nova e antiga sao iguais) */

        // inserção na t2
        int temp = ht.t1[pos1];
        ht.t1[pos1] = key;
        ht.t2[h2(temp, ht.size)] = temp;
    }
}

void 
delete(int key, hashtable_t ht) 
{
    int pos1 = h1(key, ht.size);
    if (ht.t1[pos1] == key) { // confere se o valor ta na t1
        ht.t1[pos1] = DEL;
        return; /* RETORNO ANTECIPADO */
    }

    if (ht.t1[pos1] != FREE) {
        int pos2 = h2(key, ht.size);
        if (ht.t2[pos2] == key) { // confere se o valor ta na t2
            ht.t2[pos2] = DEL;
        }
    }
}

void 
print_ht(hashtable_t ht)
{
    size_t i;

    // Tabela 1
    for (i = 0; i < ht.size; ++i) 
    {
        if (ht.t1[i] != FREE && ht.t1[i] != DEL) {
            printf("%d,T1,%ld\n", ht.t1[i], i);
        }
    }

    // Tabela 2
    for (i = 0; i < ht.size; ++i) 
    {
        if (ht.t2[i] != FREE && ht.t2[i] != DEL) {
            printf("%d,T2,%ld\n", ht.t2[i], i);
        }
    }
}
