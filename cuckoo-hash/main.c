#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main()
{
  hashtable_t ht = initHashtable(SIZE);
  freeHashtable(ht);

  return EXIT_SUCCESS;
}
