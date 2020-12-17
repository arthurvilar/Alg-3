#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

int main() {

    nodo_t *raiz = insere_nodo(NULL, 10);
    raiz = insere_nodo(raiz, 20);
    raiz = insere_nodo(raiz, 30);
    raiz = insere_nodo(raiz, 40);
    raiz = insere_nodo(raiz, 50);
    raiz = insere_nodo(raiz, 25);

    /*TESTA AS IMPRESSOES*/
    printf("Em ordem: ");
    em_ordem(raiz);

    printf("\nPre ordem: ");
    pre_ordem(raiz);

    printf("\nPos ordem: ");
    pos_ordem(raiz);

    /*TESTA A BUSCA*/
    if(busca(raiz, 10) != NULL)
        printf("\n\nbusca [10] encontrado\n");

    /*TESTA MIN E MAX*/
    nodo_t *menor = min(raiz);
    nodo_t *maior = max(raiz);
    printf("\nMenor valor: %d\nMaior valor: %d\n", menor->chave, maior->chave);

    printf("\n");

    return 1;
}
