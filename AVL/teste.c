#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

int main()
{
    nodo_t *raiz = NULL;

    raiz = insere_nodo(raiz, 10);
    raiz = insere_nodo(raiz, 20);
    raiz = insere_nodo(raiz, 30);
    raiz = insere_nodo(raiz, 40);
    raiz = insere_nodo(raiz, 50);
    raiz = insere_nodo(raiz, 45);
    raiz = insere_nodo(raiz, 48);

    /*TESTA AS IMPRESSOES*/
    printf("Em ordem:\n");
    em_ordem(raiz);

    printf("\nPre ordem:\n");
    pre_ordem(raiz);

    printf("\nPos ordem:\n");
    pos_ordem(raiz);

    /*FATOR DE BALANCEAMENTO*/
    printf("\nFB em ordem:\n");
    fb_ordem(raiz);

    /*TESTA A BUSCA*/
    if (busca(raiz, 40) != NULL)
        printf("\n\nbusca [40] encontrado");

    /*TESTA MIN E MAX*/
    nodo_t *menor = min(raiz);
    nodo_t *maior = max(raiz);
    printf("\nMenor valor: %d\nMaior valor: %d", menor->chave, maior->chave);

    /*TESTA REMOÇÃO*/
    printf("\n\nRemovendo o 40...\n");
    raiz = remove_nodo(raiz, 40);

    printf("\nEm ordem:\n");
    em_ordem(raiz);

    printf("\nPre ordem:\n");
    pre_ordem(raiz);

    printf("\nPos ordem:\n");
    pos_ordem(raiz);

    printf("\nFB em ordem:\n");
    fb_ordem(raiz);

    if (busca(raiz, 40) != NULL)
        printf("\n\nbusca [40] encontrado\n");
    else
        printf("\n\nbusca [40] não encontrado\n");

    return EXIT_SUCCESS;
}
