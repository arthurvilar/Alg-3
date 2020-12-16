#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

/* Retorna o valor mais alto entre dois inteiros */
#define MAX(a, b) ((a > b) ? (a) : (b))
/* Retorna a altura da árvore */
#define ALTURA(nodo) ((nodo) ? nodo->altura : 0) 
/* Retorna fator balanceamento do nodo */
#define FATOR(nodo) ((nodo) ? (ALTURA(nodo->esq) - ALTURA(nodo->dir)) : 0)
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
    DEBUG_ASSERT(novo_nodo != NULL, "Sem memória suficiente");

    novo_nodo->chave = chave;

    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;
    novo_nodo->altura = 0;

    return novo_nodo;
}

nodo_t*
rotaciona_dir(nodo_t *nodo)
{
    nodo_t *tmp = nodo->esq;
    nodo_t *tmp2 = tmp->dir;

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    /* Faz a rotação */
    tmp->dir = nodo;
    nodo->esq = tmp2;

    return tmp;
}

nodo_t*
rotaciona_esq(nodo_t *nodo)
{
    nodo_t *tmp = nodo->dir;
    nodo_t *tmp2 = tmp->esq;

    /* Atualiza alturas */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));
    tmp->altura = 1 + MAX(ALTURA(tmp->esq), ALTURA(tmp->dir));

    /* Faz a rotação */
    tmp->esq = nodo;
    nodo->dir = tmp2;

    return tmp;
}


nodo_t*
insere_nodo(nodo_t *nodo, int chave)
{
    if(NULL == nodo) return inicia_nodo(chave);

    if(chave < nodo->chave)
        nodo->esq = insere_nodo(nodo->esq, chave);
    else if (chave > nodo->chave)
        nodo->dir = insere_nodo(nodo->dir, chave);
    else 
        return nodo; /* chaves são idênticas */

    /* atualiza altura deste nodo */
    nodo->altura = 1 + MAX(ALTURA(nodo->esq), ALTURA(nodo->dir));

    /* fator de balanceamento deste nodo */
    int fb = FATOR(nodo);
    nodo_t *nodo_ajuste;
    if (fb > 1){ /* Desbalanceado na esquerda */
        /* Caso esq-esq ou esq-dir */
        if (chave > nodo->esq->chave)
            nodo->esq = rotaciona_esq(nodo->esq);
        nodo_ajuste = rotaciona_dir(nodo);
    } else if (fb < -1) { /* Desbalanceado na direita */
        /* Caso dir-dir ou dir-esq */
        if (chave < nodo->dir->chave)
            nodo->dir = rotaciona_dir(nodo->dir);
        nodo_ajuste = rotaciona_esq(nodo);
    } else {
        nodo_ajuste = nodo;
    }

    return nodo_ajuste;
}

nodo_t*
busca(nodo_t *nodo, int chave) 
{
    if(NULL == nodo) return NULL;

    if(chave == nodo->chave) return nodo;

    if(chave < nodo->chave)
        return busca(nodo->esq, chave);
    else
        return busca(nodo->dir, chave);
}

nodo_t*
min(nodo_t *nodo)
{
    if(NULL == nodo->esq)
        return nodo;
    else
        return min(nodo->esq);
}

nodo_t *
max(nodo_t *nodo)
{
    if (NULL == nodo->dir)
        return nodo;
    else
        return max(nodo->dir);
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
