#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"
#include "forth_const_variables.h"


//TODO free token memory after evaluating
int main() {
    GHashTable* hashtable = create(g_str_hash, g_str_equal);
    add_all_functions(hashtable); 

    if (hashtable == NULL) {
        printf("Error: Could not create hashtable.\n");
        return 1; 
    }

    int_stack_t* stack = malloc(sizeof(int_stack_t));
    int_stack_init(stack, 100); 

    token_t* token_stream = get_token_stream(stdin);
    int_stack_print(stack, stdout);

    for (int i = 0; i < MAX_TOKENS && token_stream[i].text != NULL; i++) {
        token_type_t token_type = token_stream[i].type;
        if (strcmp(token_stream[i].text, "done") == 0) {
            break;
        }else if(strcmp(token_stream[i].text, "constant") == 0){ 
            add_constant(stack, hashtable, token_stream[i+1].text);
            i++; // Skip next token because it's the constant name
        }else if (strcmp(token_stream[i].text, "variable") == 0){ 
            add_variable(stack, hashtable, token_stream[i+1].text, token_stream[i+2]);
            i += 2; // Skip next two tokens because they're the variable name and the next token
        }else if (token_type == TOKEN_NUM){ //int
            int_stack_push(stack, atoi(token_stream[i].text)); //push converted int on stack
            int_stack_print(stack, stdout);
        }else if (token_type == TOKEN_OP){ //operation
            ForthFunction func = lookup(hashtable, token_stream[i].text);
            if (func != NULL) {
                func(stack);
                int_stack_print(stack, stdout);
            } else {
                printf("Operation not found.\n");
            }
        }else if (token_type == TOKEN_STR){ //string
            ForthFunction func = lookup(hashtable, token_stream[i].text);
             if (func != NULL) {
                func(stack);
                int_stack_print(stack, stdout);
             } else {
                printf("Function not found.\n");
            }
        }
    }

    //Free the tokens
    for (int i = 0; i < MAX_TOKENS && token_stream[i].text != NULL; i++) {
        free(token_stream[i].text);
    }
    free(token_stream);
    destroy(hashtable);
    free(stack);
    return 0;
}
