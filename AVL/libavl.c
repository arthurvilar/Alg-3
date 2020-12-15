#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "libavl.h"

nodo_t*
inicia_nodo(int chave)
{
    nodo_t *novo_nodo = malloc(sizeof *novo_nodo);
    assert(NULL != novo_nodo); /* verifica se memória foi alocada para novo nodo */

    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;
    novo_nodo->pai = NULL;

    novo_nodo->chave = chave;
    novo_nodo->altura = 1;

    return novo_nodo;
}
