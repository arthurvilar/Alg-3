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
    novo_nodo->fb = 0;

    return novo_nodo;
}

int
altura(nodo_t *nodo)
{
    int h_esq, h_dir;

    if(nodo == NULL) return -1;

    h_esq = altura(nodo->esq);
    h_dir = altura(nodo->dir);

    if(h_esq > h_dir)
        return (h_esq + 1);
    else
        return (h_dir + 1);
}

nodo_t*
busca(nodo_t *nodo, int chave) 
{
    if(nodo == NULL)
        return NULL;

    if(nodo->chave == chave)
        return nodo;

    if(chave < nodo->chave)
        return busca(nodo->esq, chave);
    else
        return busca(nodo->dir, chave);
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

    return tmp;
}

nodo_t*
ajusta_avl(nodo_t *nodo, int chave)
{
    nodo_t *n_ajuste;

    //4 casos de desbalanceamento

    //esquerda esquerda
    if (nodo->fb > 1){ 
        if(chave > nodo->esq->chave) //esquerda direita
            nodo->esq = rotaciona_esq(nodo->esq);
        n_ajuste = rotaciona_dir(nodo);
    }

    //direita direita
    if (nodo->fb < -1){ 
        if(chave < nodo->dir->chave) //direita esquerda
            nodo->dir = rotaciona_dir(nodo->dir);
        n_ajuste = rotaciona_esq(nodo);
    }

    //arruma o nodo pai
    if(n_ajuste->pai != NULL){
        if(n_ajuste->pai->esq == nodo)
            n_ajuste->pai->esq = n_ajuste;
        else
            n_ajuste->pai->dir = n_ajuste;
    }

    n_ajuste->fb = 0;
    n_ajuste->esq->fb = altura(n_ajuste->esq->esq) - altura(n_ajuste->esq->dir);
    n_ajuste->dir->fb = altura(n_ajuste->dir->esq) - altura(n_ajuste->dir->dir);

    return n_ajuste;
}

nodo_t*
insere_nodo(nodo_t *nodo, int chave)
{
    //inserção normal BST
    if(nodo == NULL)
        return inicia_nodo(chave);

    if(chave < nodo->chave){
        nodo->esq = insere_nodo(nodo->esq, chave);
        nodo->esq->pai = nodo;
    }else{
        nodo->dir = insere_nodo(nodo->dir, chave);
        nodo->dir->pai = nodo;
    }
    //calcula o fator de balanceamento para checar se esta desbalanceado
    nodo->fb = altura(nodo->esq) - altura(nodo->dir);

    if(nodo->fb == 2 || nodo->fb == -2)
        nodo = ajusta_avl(nodo, chave);

    return nodo;
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