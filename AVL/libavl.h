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
nodo_t *busca(nodo_t *nodo, int chave);
nodo_t *min(nodo_t *nodo);
nodo_t *max(nodo_t *nodo);
nodo_t *insere_nodo(nodo_t *nodo, int chave);
nodo_t *remove_nodo(nodo_t *nodo, int chave); 
void pre_ordem(nodo_t *nodo);
void em_ordem(nodo_t *nodo);
void pos_ordem(nodo_t *nodo);
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
