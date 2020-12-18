#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libavl.h"

#define TAM_BUFFER 15

int main()
{
    nodo_t *raiz = NULL;
    nodo_t* (*p_funcao)(nodo_t *nodo, int chave);

    char c;
    char str_inteiro[TAM_BUFFER];
    while (EOF != (c = getchar())){
       switch(c){
       case 'i':
           p_funcao = &insere_nodo;
           break;
       case 'r':
           p_funcao = &remove_nodo;
           break;
       default:
           fprintf(stderr, "Entrada desconhecida: '%c'\n", c);
           return EXIT_FAILURE;
       }
       
       /* Obtem valor da chave como str e converte para o tipo int */
       fgets(str_inteiro, TAM_BUFFER-1, stdin);
       int inteiro = strtol(str_inteiro, NULL, 10);

       raiz = (*p_funcao)(raiz, inteiro);
    }

    em_ordem(raiz);
}
