#include "../include/cdap.h"
#include <stdlib.h>

void *CDA_malloc(size_t size) {
  void *mem = malloc(size);

  if (mem == NULL && size > 0) {
    abort();
  }

  return mem;
}

void *CDA_calloc(size_t nitems, size_t size) {
  void *mem = calloc(nitems, size);

  if (mem == NULL && nitems > 0 && size > 0) {
    abort();
  }

  return mem;
}

void *CDA_realloc(void *ptr, size_t size) {
  void *mem = realloc(ptr, size);

  if (mem == NULL && size > 0) {
    abort();
  }

  return mem;
}

void CDA_free(void *mem) {
  if (mem != NULL) {
    free(mem);
  }
}
