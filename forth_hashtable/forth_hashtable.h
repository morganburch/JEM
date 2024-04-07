#include <glib.h> //lib for hash functions
#include <stdio.h>
#include "int_stack.h"


typedef void (*ForthFunction)(int_stack_t *);

//hashtable function prototypes
extern GHashTable* create();
extern void destroy(GHashTable* hashtable);
extern void add_all_functions(GHashTable* hashtable);
extern void insert(GHashTable* hashtable, char* key, ForthFunction func);
extern ForthFunction lookup(GHashTable* hashtable, char* key);