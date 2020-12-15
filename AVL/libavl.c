#include <stdio.h>
#include <stdlib.h>

#include "libavl.h"

/* implementação alternativa de assert com a funcionalidade
 * extra de acrescentar texto para fácil diagnóstico */
#define DEBUG_ASSERT(expr, msg) \
do { \
    if (!(expr)){ \
        fprintf(stderr, "[%s:%d] %s()\n\tERRO:\t" \
                        "\tDetectado:\t%s\n" \
                        "\tEsperado:\t%s\n", \
                        __FILE__, __LINE__, __func__, \
                        msg, #expr); \
        abort(); \
    } \
} while(0)


nodo_t*
inicia_nodo(int chave)
{
    nodo_t *novo_nodo = malloc(sizeof *novo_nodo);
    DEBUG_ASSERT(NULL != novo_nodo, "Sem memória suficiente");

    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;
    novo_nodo->pai = NULL;

    novo_nodo->chave = chave;
    novo_nodo->altura = 1;

    return novo_nodo;
}

nodo_t*
rotaciona_dir(nodo_t *nodo)
{
    nodo_t *tmp = nodo->esq;
    nodo_t *tmp2 = tmp->dir;

    /* Rotaciona */
    tmp->dir = nodo;
    nodo->esq = tmp2;

    /* Atualiza pais */
    tmp->pai = nodo->pai;
    nodo->pai = tmp;
    if (tmp->dir != NULL){
        tmp->dir->pai = nodo;
    }

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    return tmp;
}

nodo_t*
rotaciona_esq(nodo_t *nodo)
{
    nodo_t *tmp = nodo->dir;
    nodo_t *tmp2 = tmp->esq;

    /* Rotaciona */
    tmp->esq = nodo;
    nodo->dir = tmp2;

    /* Atualiza pais */
    tmp->pai = nodo->pai;
    nodo->pai = tmp;
    if (tmp->esq != NULL){
        tmp->esq->pai = nodo;
    }

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    return tmp;
}
