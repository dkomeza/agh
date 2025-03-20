#pragma

struct item
{
  char name[50];
  double cena;
  int vat;
  int stock;
};

typedef struct item item;

void insert_item(item i);
void print_storage(void);

extern item storage[100];
