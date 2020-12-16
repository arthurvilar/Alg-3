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
    nodo_t *novo_nodo = malloc(sizeof(nodo_t));
    DEBUG_ASSERT(NULL != novo_nodo, "Sem memória suficiente");

    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;
    novo_nodo->pai = NULL;

    novo_nodo->chave = chave;
    novo_nodo->altura = 0;

    return novo_nodo;
}

nodo_t*
insere_nodo(nodo_t *nodo, int chave)
{
    if(nodo == NULL)
        return inicia_nodo(chave);

    if(chave < nodo->chave){
        nodo->esq = insere_nodo(nodo->esq, chave);
        nodo->esq->pai = nodo;
    }

    if (chave > nodo->chave)
    {
        nodo->dir = insere_nodo(nodo->dir, chave);
        nodo->dir->pai = nodo;
    }

    return nodo;
}

nodo_t*
busca(nodo_t *nodo, int chave) 
{
    if(nodo == NULL)
        return NULL;

    if(nodo->chave == chave)
        return nodo;

    if(chave < nodo->chave)
        busca(nodo->esq, chave);
    else
        busca(nodo->dir, chave);
}

nodo_t*
min(nodo_t *nodo)
{
    if(nodo->esq == NULL)
        return nodo;
    else
        return min(nodo->esq);
}

nodo_t *
max(nodo_t *nodo)
{
    if (nodo->dir == NULL)
        return nodo;
    else
        return max(nodo->dir);
}

nodo_t*
rotaciona_dir(nodo_t *nodo)
{
    nodo_t *tmp = nodo->esq;

    nodo->esq = tmp->dir;
    tmp->pai = nodo->pai;
    nodo->pai = tmp;
    if (tmp->dir != NULL)
        tmp->dir->pai = nodo;
    tmp->dir = nodo;

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    return tmp;
}

nodo_t*
rotaciona_esq(nodo_t *nodo)
{
    nodo_t *tmp = nodo->dir;

    nodo->dir = tmp->esq;
    tmp->pai = nodo->pai;
    nodo->pai = tmp;
    if(tmp->esq != NULL)
        tmp->esq->pai = nodo;
    tmp->esq = nodo;

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    return tmp;
}


void 
pre_ordem(nodo_t *nodo)
{
    if(nodo != NULL){
        printf("%d ", nodo->chave);
        pre_ordem(nodo->esq);
        pre_ordem(nodo->dir);
    }
}

void 
em_ordem(nodo_t *nodo)
{
    if(nodo != NULL){
        em_ordem(nodo->esq);
        printf("%d ", nodo->chave);
        em_ordem(nodo->dir);
    }
}

void 
pos_ordem(nodo_t *nodo)
{
    if(nodo != NULL){
        pos_ordem(nodo->esq);
        pos_ordem(nodo->dir);
        printf("%d ", nodo->chave);
    }
}