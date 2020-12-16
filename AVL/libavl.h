#ifndef __LIBAVL_H__
#define __LIBAVL_H__

typedef struct nodo_s {
    int chave;          /* valor deste nodo */
    int altura;         /* altura deste nodo */
    struct nodo_s *esq; /* nodo esquerdo deste nodo */
    struct nodo_s *dir; /* nodo direito deste nodo*/
} nodo_t;

/*=-=-=-implementadas-=-=-=*/
nodo_t *inicia_nodo(int chave);
nodo_t *insere_nodo(nodo_t *nodo, int chave);
nodo_t *busca(nodo_t *nodo, int chave);
nodo_t *min(nodo_t *nodo);
nodo_t *max(nodo_t *nodo);
nodo_t *rotaciona_dir(nodo_t *nodo);
nodo_t *rotaciona_esq(nodo_t *nodo);
void pre_ordem(nodo_t *nodo);
void em_ordem(nodo_t *nodo);
void pos_ordem(nodo_t *nodo);

/*=-=-=-ainda nao implementadas-=-=-=*/
/*void destroi_nodo(nodo_t *nodo);*/

#endif
