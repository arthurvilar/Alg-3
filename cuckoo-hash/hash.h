#ifndef __HASH__
#define __HASH__

#define SIZE 11
#define FREE -1     // valor inicial, espaço ainda não usado
#define DEL -2      // valor para espaço que teve chave removida

void initTable(int t[]);

int h1(int key);

int h2(int key);

void insert(int key, int t1[], int t2[]);

void delete (int key, int t1[], int t2[]);

#endif