#ifndef _LIBAVL_H_
#define _LIBAVL_H_


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


typedef struct nodo_s {
    int chave;
    int fb; //fator de balanceamento (altura_esq - altura_dir)
    struct nodo_s *esq;
    struct nodo_s *dir;
    struct nodo_s *pai;
} nodo_t;


/*=-=-=-implementadas-=-=-=*/

/* faz a busca normal de bst e retorna o nodo se achou */
nodo_t *busca(nodo_t *nodo, int chave);

/* retorna o nodo de menor valor */
nodo_t *min(nodo_t *nodo);

/* retorna o nodo de maior valor */
nodo_t *max(nodo_t *nodo);

/* faz a inserção de um novo nodo */
nodo_t *insere_nodo(nodo_t *nodo, int chave);

/* faz a remoção de um nodo */
nodo_t *remove_nodo(nodo_t *nodo, int chave);

/* faz impressão da árvore pre-ordem */
void pre_ordem(nodo_t *nodo);

/* faz impressão da árvore em-ordem */
void em_ordem(nodo_t *nodo);

/* faz impressão da árvore pos-ordem */
void pos_ordem(nodo_t *nodo);

/* faz impressão dos fatores de balanceamento de cada nodo em-ordem */
void fb_ordem(nodo_t *nodo);

/* funções de uso interno
static int _altura(nodo_t *nodo);
static int _nivel(nodo_t *nodo);
static nodo_t *_inicia_nodo(int chave);
static nodo_t *_rotaciona_dir(nodo_t *nodo);
static nodo_t *_rotaciona_esq(nodo_t *nodo);
static nodo_t *_ajusta_avl(nodo_t *nodo, int chave);
*/


#endif
