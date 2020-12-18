#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

/* retorna fator balanceamento do nodo */
#define FATOR(nodo) ((nodo) ? (altura(nodo->esq) - altura(nodo->dir)) : 0)


nodo_t*
inicia_nodo(int chave)
{
    nodo_t *novo_nodo = malloc(sizeof *novo_nodo);
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
    if (NULL == nodo) return -1;

    int h_esq = altura(nodo->esq);
    int h_dir = altura(nodo->dir);

    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

nodo_t*
busca(nodo_t *nodo, int chave) 
{
    if (NULL == nodo) return NULL;

    if (chave == nodo->chave) return nodo;

    if (chave < nodo->chave)
        return busca(nodo->esq, chave);
    else
        return busca(nodo->dir, chave);
}

nodo_t*
min(nodo_t *nodo)
{
    if (NULL == nodo->esq)
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

    if (tmp->esq != NULL)
        tmp->esq->pai = nodo;

    tmp->esq = nodo;

    return tmp;
}

nodo_t*
ajusta_avl(nodo_t *nodo, int chave)
{
    nodo_t *nodo_ajuste;

    /* 4 casos de desbalanceamento */

    /* caso esq-esq ou esq-dir */
    if (nodo->fb > 1){ 
        if (chave > nodo->esq->chave) /* caso esq-dir */
            nodo->esq = rotaciona_esq(nodo->esq);
        nodo_ajuste = rotaciona_dir(nodo);
    }

    /* caso dir-dir ou dir-esq */
    if (nodo->fb < -1){ 
        if (chave < nodo->dir->chave) /* caso dir-esq */
            nodo->dir = rotaciona_dir(nodo->dir);
        nodo_ajuste = rotaciona_esq(nodo);
    }

    /* arruma o nodo pai */
    if(nodo_ajuste->pai != NULL){
        if(nodo == nodo_ajuste->pai->esq)
            nodo_ajuste->pai->esq = nodo_ajuste;
        else
            nodo_ajuste->pai->dir = nodo_ajuste;
    }

    nodo_ajuste->fb = 0;
    nodo_ajuste->esq->fb = FATOR(nodo_ajuste->esq);
    nodo_ajuste->dir->fb = FATOR(nodo_ajuste->dir);

    return nodo_ajuste;
}

nodo_t*
insere_nodo(nodo_t *nodo, int chave)
{
    /* inserção normal BST */
    if (NULL == nodo) return inicia_nodo(chave);

    if (chave < nodo->chave){
        nodo->esq = insere_nodo(nodo->esq, chave);
        nodo->esq->pai = nodo;
    } else {
        nodo->dir = insere_nodo(nodo->dir, chave);
        nodo->dir->pai = nodo;
    }

    /* calcula o fator de balanceamento para checar
     * se esta desbalanceado */
    nodo->fb = FATOR(nodo);

    /* balancear sub-árvore se estiver desbalanceada */
    if ((nodo->fb > 1) || (nodo->fb < -1))
        nodo = ajusta_avl(nodo, chave);

    return nodo;
}

nodo_t*
remove_nodo(nodo_t *nodo, int chave)
{
    if (NULL == nodo) return nodo;

    /*-----FAZ A REMOÇÃO----*/

    if (chave < nodo->chave) {
        /* chave menor continua a busca na esquerda */
        nodo->esq = remove_nodo(nodo->esq, chave);
    } else if (chave > nodo->chave) {
        /* chave maior continua a busca na direita */
        nodo->dir = remove_nodo(nodo->dir, chave);
    } else {
        /* chave igual a do nodo (achou o nodo) faz a remoção */
        if ((NULL == nodo->esq) || (NULL == nodo->dir)){
            /* nodo possui zero ou um filho */
            nodo_t *tmp = nodo->esq ? nodo->esq : nodo->dir;
            if (NULL == tmp){ /* sem filho */
                tmp = nodo;
                nodo = NULL;
            } else { /* com um filho */
                /* @todo se não funcionar tem que arrumar
                 * os ponteiros de pai e filho manualmente */
                nodo = tmp;
            }

            free(tmp);
        } else {
            /* nodo com dois filhos */
            nodo_t *sucessor = min(nodo->dir);

            nodo->chave = sucessor->chave;
            nodo->dir = remove_nodo(nodo->dir, sucessor->chave);
        }
    }

    /*-----FAZ O BALANCEAMENTO----*/

    /* if (NULL == nodo) return nodo; */
    nodo->fb = FATOR(nodo);

    /* caso esq-esq ou esq-dir */
    if (nodo->fb > 1){
        if (FATOR(nodo->esq) < 0) /* caso esq-dir */
            nodo->esq = rotaciona_esq(nodo->esq);
        return rotaciona_dir(nodo);
    }

    /* caso dir-dir ou dir-esq */
    if (nodo->fb < -1){
        if (FATOR(nodo->dir) > 0) /* caso dir-esq */
            nodo->dir = rotaciona_dir(nodo->dir);
        return rotaciona_dir(nodo);
    }

    return nodo;
}

static int
_nivel(nodo_t *nodo)
{
    int nivel = 0;
    for ( ; nodo->pai != NULL ; nodo = nodo->pai )
        ++nivel;

    return nivel;
}

void 
pre_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
        pre_ordem(nodo->esq);
        pre_ordem(nodo->dir);
    }
}

void 
em_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        em_ordem(nodo->esq);
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
        em_ordem(nodo->dir);
    }
}

void 
fb_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        fb_ordem(nodo->esq);
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
        fb_ordem(nodo->dir);
    }
}

void 
pos_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        pos_ordem(nodo->esq);
        pos_ordem(nodo->dir);
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
    }
}
