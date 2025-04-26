#ifndef MEMORIZER_H
#define MEMORIZER_H

typedef struct {
  void **pointers;    
  size_t count;       
  size_t capacity;    
} Memorizer;

void memorizer_init(Memorizer *m);
void *memorizer_alloc(Memorizer *m, size_t size);
void memorizer_free_ptr(Memorizer *m, void *ptr);
void memorizer_free_all(Memorizer *m);
void memorizer_destroy(Memorizer *m);


#endif // MEMORIZER_H