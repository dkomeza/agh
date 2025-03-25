#include "storage.h"
#include <stdio.h>

item storage[100];
int size = 0;

void insert_item(item i) {
  
}

void print_storage(void)
{
  for (int i = 0; i < size; i++)
  {
    printf("Item no: %d, name: %s, price: %f, vat: %d%, state: %d", i, storage[i].name, storage[i].cena, storage[i].vat, storage[i].stock);
  }
}

