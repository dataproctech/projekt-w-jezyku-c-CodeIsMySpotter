#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <stdlib.h>
#include <stddef.h>

#define INITIAL_CAPACITY 16


typedef enum {
  ERROR_NONE,
  ERROR_FILE_NOT_FOUND,
  ERROR_PERMISSION_DENIED,
  ERROR_OUT_OF_MEMORY,
  ERROR_INVALID_ARGUMENT,
  ERROR_UNKNOWN,
  OK,
} ErrorCode;


typedef struct {
  ErrorCode error_code;
  void *value;
} OptionType;


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

#endif 
