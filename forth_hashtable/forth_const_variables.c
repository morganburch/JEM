#include <stdio.h>
#include <stdint.h>
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
//if key word "variable" is tokens[i].text, key is tokens[i+1].text, and nextToken is tokens[i+2].text
//int add_variable(int_stack_t* stk, GHashTable* hashtable, const char* key, token_t next token){ 
    //int val; 
    //step 1: allocate memory for new variable and save this memory location somewhere associated with the variable key (maybe userHashtable)
    //step 2: check nextToken
        //if next token = "!" then pop top from stack and save that int as variable value 
        //if next token = "+!" then update the variable value by adding the top of stack to the current value
        //if next token = "@" then push the variable value on the stack
        //if none of these, push the memory location on the stack (ex. 1055)

int add_variable(int_stack_t* stk, GHashTable* hashtable, const char* key, token_t next_token) {
    int* memory_location = (int*)malloc(sizeof(int));

    // Make hashtable entries for memory location and variable value 
    user_insert(hashtable, strdup(key), *memory_location);
    user_insert(hashtable, g_strdup_printf("%s_value", key), 0);

    // Check next token
    if (strcmp(next_token.text, "!") == 0) { // Assign value to variable 
        int value; 
        int_stack_pop(stk, &value);
        g_hash_table_replace(hashtable, g_strdup_printf("%s_value", key), GINT_TO_POINTER(value));
    } else if (strcmp(next_token.text, "+!") == 0) { // Update value
        int val; 
        int_stack_pop(stk, &val);
        int current_value = GPOINTER_TO_INT(user_lookup(hashtable, g_strdup_printf("%s_value", key)));
        int newVal = current_value + val; 
        g_hash_table_replace(hashtable, g_strdup_printf("%s_value", key), GINT_TO_POINTER(newVal));
    } else if (strcmp(next_token.text, "@") == 0) { // Push the value of the variable onto the stack
        int value = GPOINTER_TO_INT(user_lookup(hashtable, g_strdup_printf("%s_value", key)));
        int_stack_push(stk, value);
    } else { // Push memory location to stack
        intptr_t memory_location_as_int = (intptr_t)memory_location;
        int_stack_push(stk, memory_location_as_int);
    }
    return 0;
}






