#include "libavl.h"

nodo_t *inicia_nodo(int chave) {
    nodo_t *n = (nodo_t*)malloc(sizeof(nodo_t));
    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    return n;
}