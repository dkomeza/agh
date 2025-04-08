#include "utils.h"

#include <stdlib.h>

void destroy_dumb_vector(struct dumb_vector *v)
{
  if (v != NULL)
  {
    free(v->data);
    free(v);
  }
}

struct dumb_vector *create_dumb_vector(int capacity)
{
  struct dumb_vector *v = malloc(sizeof(struct dumb_vector));

  if (capacity <= 0)
  {
    capacity = 16; // default capacity
  }

  if (v == NULL)
  {
    return NULL;
  }
  v->size = 0;
  v->capacity = capacity;
  v->data = calloc(capacity, sizeof(int));
  if (v->data == NULL)
  {
    free(v);
    return NULL;
  }
  return v;
}

void push_back(struct dumb_vector *v, int value)
{
  if (v->size == v->capacity)
  {
    v->capacity *= 2;
    v->data = realloc(v->data, v->capacity * sizeof(int));
  }
  v->data[v->size] = value;
  v->size++;
}

int get(struct dumb_vector *v, int index)
{
  if (index < 0)
  {
    index += v->size;
  }
  return v->data[index];
}
void set(struct dumb_vector *v, int index, int value)
{
  if (index < 0)
  {
    index += v->size;
  }
  v->data[index] = value;
}
int size(struct dumb_vector *v)
{
  return v->size;
}
int capacity(struct dumb_vector *v)
{
  return v->capacity;
}
int is_empty(struct dumb_vector *v)
{
  return v->size == 0;
}
int is_full(struct dumb_vector *v)
{
  return v->size == v->capacity;
}
