#ifndef __LIBAVL_H__
#define __LIBAVL_H__

/* Retorna o valor mais alto entre dois inteiros */
#define MAX(a, b) ((a > b) ? (a) : (b))
/* Retorna a altura da árvore */
#define ALTURA(nodo) ((nodo) ? nodo->altura : 0) 
/* Retorna fator balanceamento do nodo */
#define FATOR(nodo) ((nodo) ? ALTURA(nodo->esq) - ALTURA(nodo->dir) ? 0)

typedef struct nodo_s {
    int chave;
    int fb; //fator de balanceamento (altura_esq - altura_dir)
    struct nodo_s *esq;
    struct nodo_s *dir;
    struct nodo_s *pai;
} nodo_t;

/*=-=-=-implementadas-=-=-=*/
nodo_t *inicia_nodo(int chave);
int altura(nodo_t *nodo);
nodo_t *busca(nodo_t *nodo, int chave);
nodo_t *min(nodo_t *nodo);
nodo_t *max(nodo_t *nodo);
nodo_t *rotaciona_dir(nodo_t *nodo);
nodo_t *rotaciona_esq(nodo_t *nodo);
nodo_t *insere_nodo(nodo_t *nodo, int chave);
nodo_t *remove_nodo(nodo_t *nodo, int chave); 
void pre_ordem(nodo_t *nodo);
void em_ordem(nodo_t *nodo);
void pos_ordem(nodo_t *nodo);
void fb_ordem(nodo_t *nodo);

/*=-=-=-ainda nao implementadas-=-=-=*/
/*void destroi_nodo(nodo_t *nodo);*/

#endif
