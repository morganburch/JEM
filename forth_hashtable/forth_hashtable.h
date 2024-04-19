#include <glib.h> //hastable library
#include <stdio.h>
#include "int_stack.h"
#include <token.h>


typedef int (*ForthFunction)(int_stack_t *);

//hashtable function prototypes
extern GHashTable* create();
extern void destroy(GHashTable* hashtable);
extern void add_all_functions(GHashTable* hashtable);
extern void insert(GHashTable* hashtable, const char* key, ForthFunction func);
extern ForthFunction lookup(GHashTable* hashtable, const char* key);
extern void user_insert(GHashTable* hashtable, const char* key, token_t* tokens);
extern token_t* user_lookup(GHashTable* hashtable, const char* key);