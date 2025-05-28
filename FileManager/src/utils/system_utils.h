#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <stddef.h>

#define MAX_MSG_LENGTH 256


// Error code enum
typedef enum {
    ERR,
    OK,
} ErrorCode;

// Typ alias dla stringów
typedef char* String;

// Result struct
typedef struct {
    ErrorCode error_code;
    void *value;
    char message[256];
} Result;

// Result helpers
Result ok(void *value, const char *msg);
Result err(const char *msg);
void *unwrap(Result res);
void *unwrap_or(Result res, void *default_value);

// Dynamic list
#define INITIAL_CAPACITY 16

typedef struct {
    void **items;
    size_t size;
    size_t capacity;
} List;

// List management
Result list_init();
Result list_deinit(List *list, void (*free_func)(void *));
Result list_add(List *list, void *item);
Result list_get(List *list, size_t index);
Result list_set(List *list, size_t index, void *item);
Result list_remove(List *list, size_t index, void (*free_func)(void *));

// Helpers for primitive types
#define def_int(value) ((void *)&(int){value})
#define def_char(value) ((void *)&(char){value})

#endif // SYSTEM_UTILS_H
