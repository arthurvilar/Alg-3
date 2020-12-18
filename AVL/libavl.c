#include <stdio.h>
#include <stdlib.h>

#include "libavl.h"


/* retorna a altura do nodo */
static int
_altura(nodo_t *nodo)
{
    if (NULL == nodo) return -1;

    int h_esq = _altura(nodo->esq);
    int h_dir = _altura(nodo->dir);

    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

/* retorna fator balanceamento do nodo */
#define FATOR(nodo) ((nodo) ? (_altura(nodo->esq) - _altura(nodo->dir)) : 0)

static int
_nivel(nodo_t *nodo)
{
    int nivel = 0;
    for ( ; nodo->pai != NULL ; nodo = nodo->pai )
        ++nivel;

    return nivel;
}

/* aloca espaço, inicia ponteiros e retorna o nodo */
static nodo_t*
_inicia_nodo(int chave)
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

/* função de rotação para a direita vista em aula */
static nodo_t*
_rotaciona_dir(nodo_t *nodo)
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

/* função de rotação para a esquerda vista em aula */
static nodo_t*
_rotaciona_esq(nodo_t *nodo)
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

/* faz o auto balanceamento da arvore, retorna o novo nodo raiz */
static nodo_t*
_ajusta_avl(nodo_t *nodo, int chave)
{
    nodo_t *nodo_ajuste;

    /* 4 casos de desbalanceamento */

    /* caso esq-esq ou esq-dir */
    if (nodo->fb > 1){ 
        if (chave > nodo->esq->chave) /* caso esq-dir */
            nodo->esq = _rotaciona_esq(nodo->esq);
        nodo_ajuste = _rotaciona_dir(nodo);
    }

    /* caso dir-dir ou dir-esq */
    if (nodo->fb < -1){ 
        if (chave < nodo->dir->chave) /* caso dir-esq */
            nodo->dir = _rotaciona_dir(nodo->dir);
        nodo_ajuste = _rotaciona_esq(nodo);
    }

    /* arruma o nodo pai */
    if(nodo_ajuste->pai != NULL){
        if(nodo == nodo_ajuste->pai->esq)
            nodo_ajuste->pai->esq = nodo_ajuste;
        else
            nodo_ajuste->pai->dir = nodo_ajuste;
    }

    /* atualiza o fb */
    nodo_ajuste->fb = 0;
    nodo_ajuste->esq->fb = FATOR(nodo_ajuste->esq);
    nodo_ajuste->dir->fb = FATOR(nodo_ajuste->dir);

    return nodo_ajuste;
}

/* faz a busca normal de bst e retorna o nodo se achou */
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

/* retorna o nodo de menor valor */
nodo_t*
min(nodo_t *nodo)
{
    if (NULL == nodo->esq)
        return nodo;
    else
        return min(nodo->esq);
}

/* retorna o nodo de maior valor */
nodo_t *
max(nodo_t *nodo)
{
    if (NULL == nodo->dir)
        return nodo;
    else
        return max(nodo->dir);
}

/* faz a inserção de um novo nodo */
nodo_t*
insere_nodo(nodo_t *nodo, int chave)
{
    /* inserção normal BST */
    if (NULL == nodo) return _inicia_nodo(chave);

    if (chave < nodo->chave){
        nodo->esq = insere_nodo(nodo->esq, chave);
        nodo->esq->pai = nodo;
    } else {
        nodo->dir = insere_nodo(nodo->dir, chave);
        nodo->dir->pai = nodo;
    }

    /* calcula o fator de balanceamento para checar
       se esta desbalanceado */
    nodo->fb = FATOR(nodo);

    /* balancear sub-árvore se estiver desbalanceada */
    if ((nodo->fb > 1) || (nodo->fb < -1))
        nodo = _ajusta_avl(nodo, chave);

    return nodo;
}

/* faz a remoção de um nodo */
nodo_t*
remove_nodo(nodo_t *nodo, int chave)
{
    if (NULL == nodo) return nodo;

    /*-----FAZ A REMOÇÃO----*/

    /* chave menor continua a busca na esquerda */
    if (chave < nodo->chave) {
        nodo->esq = remove_nodo(nodo->esq, chave);
    
    /* chave maior continua a busca na direita */
    } else if (chave > nodo->chave) {
        nodo->dir = remove_nodo(nodo->dir, chave);
    
    /* chave igual a do nodo (achou o nodo) faz a remoção */
    } else {
        /* nodo possui zero ou um filho */
        if ((NULL == nodo->esq) || (NULL == nodo->dir)){
            nodo_t *tmp = nodo->esq ? nodo->esq : nodo->dir;
            
            if (NULL == tmp){   /* sem filho */
                tmp = nodo;
                nodo = NULL;
            }
            else                /* com um filho */
                nodo = tmp;

            free(tmp);

        /* nodo possui dois filhos */
        } else {
            nodo_t *sucessor = min(nodo->dir);

            nodo->chave = sucessor->chave;
            nodo->dir = remove_nodo(nodo->dir, sucessor->chave);
        }
    }

    if (NULL == nodo) return nodo;

    /*-----FAZ O BALANCEAMENTO----*/

    nodo->fb = FATOR(nodo);

    /* caso esq-esq ou esq-dir */
    if (nodo->fb > 1){
        if (FATOR(nodo->esq) < 0) /* caso esq-dir */
            nodo->esq = _rotaciona_esq(nodo->esq);
        return _rotaciona_dir(nodo);
    }

    /* caso dir-dir ou dir-esq */
    if (nodo->fb < -1){
        if (FATOR(nodo->dir) > 0) /* caso dir-esq */
            nodo->dir = _rotaciona_dir(nodo->dir);
        return _rotaciona_dir(nodo);
    }

    return nodo;
}

/* -=-=-= FUNÇÕES DE UTILIDADE PARA TESTAR SE É AVL =-=-=- */

/* faz impressão da árvore pre-ordem */
void 
pre_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
        pre_ordem(nodo->esq);
        pre_ordem(nodo->dir);
    }
}

/* faz impressão da árvore em-ordem */
void 
em_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        em_ordem(nodo->esq);
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
        em_ordem(nodo->dir);
    }
}

/* faz impressão da árvore pos-ordem */
void 
pos_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        pos_ordem(nodo->esq);
        pos_ordem(nodo->dir);
        printf("%d,%d\n", nodo->chave, _nivel(nodo));
    }
}

/* faz impressão dos fatores de balanceamento de cada nodo em-ordem */
void 
fb_ordem(nodo_t *nodo)
{
    if (nodo != NULL){
        fb_ordem(nodo->esq);
        printf("%d:\t%d,%d\n", nodo->fb, nodo->chave, _nivel(nodo));
        fb_ordem(nodo->dir);
    }
}