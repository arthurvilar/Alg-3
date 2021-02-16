#include "hash.h"

void initTable(int t[]) {
    for (int i = 0; i < SIZE; i++)
        t[i] = -1;  //posição livre
}

int h1(int key) {
    return (key % SIZE);
}

int h2(int key) {
    return (floor(SIZE * ((key * 0.9) - floor(key * 0.9))));
}

/* 
    a inserção é sempre na t1.
    primeiro checa se a posição h1(key) esta disponivel na t1,
    se estiver insere, se não, houve uma colisão,
    então insere o valor que ta na posição h1(key) de t1
    na posição h2(t1[h1]) na t2,
    e depois insere key em t1[h1(key)] 
*/
void insert(int key, int t1[], int t2[]) {
    int pos1 = h1(key);
    
    //inserção na tabela 1
    if (t1[pos1] == -1 || t1[pos1] == -2) {
        t1[pos1] = key;
    }
    else if (h1(t1[pos1]) == pos1) {    //colisão em T1
        int temp = t1[pos1];
        
        if (key == t1[pos1]) {      //se chave nova e antiga sao iguais ignora
            return;
        } else {
            t1[pos1] = key;
            t2[h2(temp)] = temp;
        }

        /*
        Implementação 2 (sem usar temp):
        
        int temp = t1[pos1];

        if (key == t1[pos1]) {
            return;
        } else {
            t2[h2(t1[pos1])] = t1[pos1];
            t1[pos1] = key;
        }
        */
    }
}