#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"


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

    print_ht(ht);

    free(inputs); // libera entradas obtidas
    freeHashtable(ht); // libera campos t1 e t2 da memória

    return EXIT_SUCCESS;
}
