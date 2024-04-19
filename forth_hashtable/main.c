#include <stdio.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"

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
        token_type_t token_type = classify_token(token_stream[i].text);
         if (strcmp(token_stream[i].text, "done") == 0) {
            break;
        }
        if (token_type == 0){ //int
            int_stack_push(stack, atoi(token_stream[i].text)); //push converted int on stack
            int_stack_print(stack, stdout);
        }
        else if (token_type == 1){ //operation
            ForthFunction func = lookup(hashtable, token_stream[i].text);
            if (func != NULL) {
                func(stack);
                int_stack_print(stack, stdout);
            } else {
                printf("Operation not found.\n");
            }
        }
        else if (token_type == 3){ //string
            ForthFunction func = lookup(hashtable, token_stream[i].text);
             if (func != NULL) {
                func(stack);
                int_stack_print(stack, stdout);
             } else {
                printf("Function not found.\n");
            }
        }
    }

    destroy(hashtable);
    free(stack);

    return 0;
}
