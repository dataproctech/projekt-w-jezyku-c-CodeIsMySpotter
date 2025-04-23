#include "system_utils.h"
#include <string.h>


OptionType memorizer_init(Memorizer *m) {
    m->count = 0;
    m->capacity = INITIAL_CAPACITY;
    m->pointers = malloc(m->capacity * sizeof(void *));

    if (m->pointers == NULL) {
        m->capacity = 0;
        m->count = 0;
        return OptionType{.error_code = ERROR_OUT_OF_MEMORY, .value = NULL};
    }
    return OptionType{.error_code = OK, .value = NULL};
}



void *memorizer_alloc(Memorizer *m, size_t size) {
  if (m->count >= m->capacity) {
      m->capacity *= 2;
      m->pointers = realloc(m->pointers, m->capacity * sizeof(void *));
  }

  void *ptr = malloc(size);
  if (ptr != NULL) {
      m->pointers[m->count++] = ptr;
  }
  return ptr;
}

void memorizer_free_ptr(Memorizer *m, void *ptr) {
  for (size_t i = 0; i < m->count; ++i) {
      if (m->pointers[i] == ptr) {
          free(ptr);
          m->pointers[i] = m->pointers[m->count - 1]; 
          m->count--;
          return;
      }
  }
}

void memorizer_free_all(Memorizer *m) {
  for (size_t i = 0; i < m->count; ++i) {
      free(m->pointers[i]);
  }
  m->count = 0;
}

void memorizer_destroy(Memorizer *m) {
  memorizer_free_all(m);
  free(m->pointers);
  m->pointers = NULL;
  m->capacity = 0;
}