#ifndef __HASH__
#define __HASH__

#define SIZE 11

void initTable(int t[]);

int h1(int key);
int h2(int key);

void insert(int key, int t1[], int t2[]);

#endif