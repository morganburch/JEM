#ifndef forth_const_variables
#define forth_const_variables

#include <glib.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"


int add_constant(int_stack_t* stk, GHashTable* hashtable, const char* key);
int add_variable(int_stack_t* stk, GHashTable* hashtable, const char* key, token_t next_token);

#endif
