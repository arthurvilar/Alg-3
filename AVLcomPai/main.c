#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

int main() {
    
    nodo_t *raiz = NULL;
    
    raiz = insere_nodo(raiz, 10);
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

    /*FATOR DE BALANCEAMENTO*/
    printf("\n\nFB em ordem: ");
    fb_ordem(raiz);

    /*TESTA A BUSCA*/
    if(busca(raiz, 40) != NULL)
        printf("\n\nbusca [40] encontrado\n");

    /*TESTA MIN E MAX*/
    nodo_t *menor = min(raiz);
    nodo_t *maior = max(raiz);
    printf("\nMenor valor: %d\nMaior valor: %d\n", menor->chave, maior->chave);

    /*TESTA REMOÇÃO*/
    printf("\n\nRemovendo o 40...\n");
    raiz = remove_nodo(raiz, 40);

    printf("\nEm ordem: ");
    em_ordem(raiz);

    printf("\nPre ordem: ");
    pre_ordem(raiz);

    printf("\nPos ordem: ");
    pos_ordem(raiz);

    printf("\n\nFB em ordem: ");
    fb_ordem(raiz);

    if (busca(raiz, 40) != NULL)
        printf("\n\nbusca [40] encontrado\n");
    else
        printf("\n\nbusca [40] não encontrado\n");

    printf("\n");

    return 1;
}