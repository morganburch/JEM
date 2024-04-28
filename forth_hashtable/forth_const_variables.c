#include <stdio.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"

#define STORE_VALUE 1
#define ADD_VALUE 2
#define FETCH_VALUE 3

/*Variables and Constants: 

Variables in FORTH: 
- variable key word
- next word is the name of the variable 
- calling the variable itself just returns the memory location
- @ dereferences and pushes the value on the stack
- ! assigns a value to the variable 
- +! updates the value by whatever is top of stack

Constants: 
- constants represent values, not locations so no need to dereference w @
- just declare in one like like (<int> constant <variable name>) 
- ex. 42 constant answer // 2 answer * 
*/

 //if curr token = constant then
 //if no int on stack before constant, stack underflow/error
 //remember to pass next token as key when calling this method


int add_constant(int_stack_t* stk, GHashTable* hashtable, const char* key) {
    int val;
    int_stack_pop(stk, &val); //get last val from stack
    user_insert(hashtable, key, val); //add to hashtable 
    return 0; 
}
/*
int add_variable(int_stack_t stk, GHashTable* hashtable, const char* key, token_t nextToken){
    int value;
    switch (nextToken) {
        case STORE_VALUE:  // !
            int_stack_pop(forth->stack, &value);
            g_hash_table_replace(forth->variables, g_strdup(key), GINT_TO_POINTER(value));
            break;
        case ADD_VALUE:  // +!
            int_stack_pop(forth->stack, &value);
            int old_value = GPOINTER_TO_INT(g_hash_table_lookup(forth->variables, key));
            g_hash_table_replace(forth->variables, g_strdup(key), GINT_TO_POINTER(old_value + value));
            break;
        case FETCH_VALUE:  // @
            value = GPOINTER_TO_INT(g_hash_table_lookup(forth->variables, key));
            int_stack_push(forth->stack, value);
            break;
        default:
            // Handle error or other cases
            break;
    }
}
}
*/




