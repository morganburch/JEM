#include <stdio.h>
#include "forth_hashtable.h"
#include "int_stack.h"
#include "token.h"


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
 /*
int add_constant(int_stack_t* stk, GHashTable* hashtable, const char* key){ 
    int val;
    int_stack_pop(stk, &val);
    char char_val = (char)val;
    token_t* token_stream = classify_token(char_val);
    user_insert(hashtable, key, token_stream);
}
*/
int add_constant(int_stack_t* stk, GHashTable* hashtable, const char* key) {
    int val;
    char char_val = (char) val;

    //making a char stream to pass to classify token since cant do just one char
    char* char_stream = (char*) malloc(2 * sizeof(char)); 
    char_stream[0] = char_val;
    char_stream[1] = '\0'; // Null-terminate the string
    
    token_t token_stream = classify_token(char_stream);
    
    free(char_stream); 
    return 0; // Indicate success
}
