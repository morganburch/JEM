#include "forth_hashtable.h"
#include <glib.h>
#include <stdio.h>
#include "int_stack.h"

GHashTable* create(GHashFunc hash_func, GEqualFunc key_equal_func) {
    return g_hash_table_new(hash_func, key_equal_func);
}

void destroy(GHashTable* hashtable) {
    g_hash_table_destroy(hashtable);
}

// FORTH primitive functions
void insert(GHashTable* hashtable, const char* key, ForthFunction func) {
    g_hash_table_insert(hashtable, (gpointer)key, func);
}

// returns a callable function to use in the user interface
ForthFunction lookup(GHashTable* hashtable, const char* key) {
    return (ForthFunction)g_hash_table_lookup(hashtable, key);
}

// add functions to the FORTH map
void add_all_functions(GHashTable* hashtable) {
    insert(hashtable, "dup", (ForthFunction)int_stack_dup);
    insert(hashtable, "2dup", (ForthFunction)int_stack_2dup);
    insert(hashtable, "swap", (ForthFunction)int_stack_swap);
    insert(hashtable, "+", (ForthFunction)int_stack_add);
    insert(hashtable, "-", (ForthFunction)int_stack_subtract);
    insert(hashtable, "*", (ForthFunction)int_stack_multiply);
    insert(hashtable, "/", (ForthFunction)int_stack_divide);
    insert(hashtable, ".", (ForthFunction)int_stack_drop);
    insert(hashtable, "drop", (ForthFunction)int_stack_drop);
    insert(hashtable, "2drop", (ForthFunction)int_stack_2drop);
    insert(hashtable, "over", (ForthFunction)int_stack_over);
    insert(hashtable, "2over", (ForthFunction)int_stack_2over);
    //insert(hashtable, "variable", );
    //insert(hashtable, "constant", );
    //TODO add constant and variable to hashtable 
}

// user hashtable
void user_insert(GHashTable* hashtable, const char* key, int value) {
    g_hash_table_insert(hashtable, (gpointer)key, GINT_TO_POINTER(value));
}

token_t* user_lookup(GHashTable* hashtable, const char* key) {
    return (token_t*)g_hash_table_lookup(hashtable, key);
}
