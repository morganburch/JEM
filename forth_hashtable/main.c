#include <stdio.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"

int main() {
    GHashTable* hashtable = create(g_str_hash, g_str_equal);
    add_all_functions(hashtable);

    if (hashtable == NULL) {
        printf("Error: Could not create hashtable.\n");
        return 1; // Return an error code
    }

    int_stack_t* stack = malloc(sizeof(int_stack_t));
    int_stack_init(stack, 100); 
    int_stack_push(stack, 42);

    ForthFunction func = lookup(hashtable, "dup");
    if (func != NULL) {
        func(stack);
        int top_value;
        int_stack_top(stack, &top_value);
        printf("Top of stack after dup: %d\n", top_value);
    } else {
        printf("Function not found.\n");
    }

    destroy(hashtable);
    free(stack);

    return 0;
}
