#include <stdio.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"
#include "forth_const_variables.h"

int main() {
    //takes string and ForthFunction
    GHashTable* hashtable = create(g_str_hash, g_str_equal);
    add_all_functions(hashtable);

    //takes string and token_t*
    GHashTable* user_hashtable = create(g_str_hash, g_str_equal);

    if (hashtable == NULL) {
        printf("Error: Could not create hashtable.\n");
        return 1; // Return an error code
    }

    int_stack_t* stack = malloc(sizeof(int_stack_t));
    int_stack_init(stack, 100); 
    int_stack_push(stack, 42);
    printf("Original Stack: \n");
    int_stack_print(stack, stdout);

    ForthFunction func = lookup(hashtable, "dup");
    if (func != NULL) {
        func(stack);
        printf("After function: \n");
        int_stack_print(stack, stdout);
    } else {
        printf("Function not found.\n");
    }

    int_stack_push(stack, 42);
    int_stack_push(stack, 2);

    char* token_stream[3]; 
    token_stream[0] = strdup("constant"); 
    token_stream[1] = strdup("practice"); 
    token_stream[2] = strdup("*");

    for(int i = 0; i < 3; i++) {
        if(strcmp(token_stream[i], "constant") == 0) {
            if(i+1 < 3) {
                //call add_constant() with the next token as the key
                add_constant(stack, hashtable, token_stream[i+1]);
                i++; //skip next token 

                // Retrieve the constant from the hashtable
                int constant = GPOINTER_TO_INT(g_hash_table_lookup(hashtable, token_stream[i]));

                int val;
                int_stack_pop(stack, &val); //get last val from stack
                val *= constant;
                int_stack_push(stack, val); //push the result back to the stack
                printf("Adding constant value 84: \n");
                int_stack_print(stack, stdout); 
            } else {
                printf("Error: No key provided after 'constant'\n");
            }
        }
    }

    for(int i = 0; i < 3; i++) {
        free(token_stream[i]);
    }

        destroy(hashtable);
        free(stack);

        return 0;
    }