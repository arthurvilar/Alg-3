#include "hash.h"

void initTable(int t[]) {
    for (int i = 0; i < SIZE; i++)
        t[i] = FREE;  // posição livre
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
    
    // inserção na t1
    if (t1[pos1] == -1 || t1[pos1] == -2) {
        t1[pos1] = key;
    }
    else if (h1(t1[pos1]) == pos1) {    // colisão em T1
        int temp = t1[pos1];
        
        if (key == t1[pos1]) {      // se chave nova e antiga sao iguais ignora
            return;
        } else {                    // inserção na t2
            t1[pos1] = key;
            t2[h2(temp)] = temp;
        }
    }
}

void delete (int key, int t1[], int t2[]) {
    int pos1 = h1(key);
    int pos2 = h2(key);

    if (t1[pos1] == key) {          // confere se o valor ta na t1
        t1[pos1] = DEL;
    }
    else if (t1[pos1] != FREE) {
        if (t2[pos2] == key)        // confere se o valor ta na t2
            t2[pos2] = DEL;
    }
}