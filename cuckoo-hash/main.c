#include <stdio.h>
#include <stdlib.h>
#include <string.h> // para strchr()
#include <assert.h>

#include "hash.h"


typedef struct input_s {
    int key; // valor a ser inserido ou removido na hashtable
    char action; // i (INSERE); r (REMOVE); '\0' (INATIVO)
} input_t;

/* deserialização do conteúdo dos arquivos de entrada para um array de
 *  struct input_s contendo chaves e instruções */
static input_t* 
getInputs(size_t size)
{
    input_t *inputs = calloc(1, size * sizeof(input_t));
    if (NULL == inputs) return NULL;

    char line[256]; // tamanho mais que o suficiente
    for (size_t i=0; i < size; ++i) 
    {
        if ( NULL == fgets(line, sizeof(line)-1, stdin) ) // obtem linha atual da entrada
            break; // BREAK ANTECIPADO (não há mais linhas a serem lidas)

        inputs[i].action = line[0]; // ação é o primeiro char da linha

        char *strkey = 1 + strchr(line, ' '); // obtem posicao do key no string
        inputs[i].key = (int)strtol(strkey, NULL, 10); // converte key do input para int
    }

    return inputs;
}

int main()
{
    const size_t SIZE = 11; // tamanho fixo para teste (m = 11)

    /* 'inputs' é alocado dinamicamente de forma a mapear as entradas
     *  fornecidas pelo professor em um struct contendo campos para
     *  chave e ação obtidos por linha */
    input_t *inputs = getInputs(SIZE);
    assert(NULL != inputs);
    
    /* 'ht' é uma variável local, porém seus campos t1 e t2 são 
     *  alocados dinamicamente (precisam ser liberados manualmente) */
    hashtable_t ht = initHashtable(SIZE);

    /* percore as entradas uma a uma, verifica a ação vinculada
     *  e a efetua na chave e hashtable correspondente */
    for (size_t i=0; i < SIZE; ++i) 
    {
        switch (inputs[i].action) {
        case 'i': // INSERIR VALOR NA HASHTABLE
            insert(inputs[i].key, ht);
            break;
        case 'r': // REMOVER VALOR DA HASHTABLE
            delete(inputs[i].key, ht);
            break;
        case '\0': default: // NÃO HÁ MAIS ENTRADAS A SEREM LIDAS
            break;
        }
    }

    free(inputs); // libera entradas obtidas
    freeHashtable(ht); // libera campos t1 e t2 da memória

    return EXIT_SUCCESS;
}
