/* Retorna o valor mais alto entre dois inteiros */
#define MAX(a, b) ((a > b) ? (a) : (b))
/* Retorna a altura da árvore */
#define ALTURA(nodo) ((nodo) ? nodo->altura : 0) 
/* Retorna fator balanceamento do nodo */
#define FATOR(nodo) ((nodo) ? ALTURA(nodo->esq) - ALTURA(nodo->dir) ? 0)

typedef struct nodo_s {
    int chave;
    struct nodo_s *esq;
    struct nodo_s *dir;
    struct nodo_s *pai;

    int altura;
} nodo_t;

nodo_t* nodo_inicia(int chave);
void nodo_destroi(nodo_t *nodo);

nodo_t* nodo_rotaciona_dir(nodo_t *nodo);
nodo_t* nodo_rotaciona_esq(nodo_t *nodo);
nodo_t* nodo_insere(nodo_t *nodo, int chave);
