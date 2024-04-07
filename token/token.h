/*token.h -- define token interface (constructor esque)

You will create an abstract datatype (struct token_t) that will have a
 token class (enum token_type_t) and its text (a string).  
*/
#ifndef INT_TOKEN_H //Prevent multiple inclusions of the same header file 
#define INT_TOKEN_H
#define MAX_TOKENS 1000

#include <stdio.h>

typedef enum{ //new data type
    TOKEN_NUM, //0
    TOKEN_OP, //1
    TOKEN_SYM, //2
    TOKEN_STR, //3
    TOKEN_UNKNOWN, //4
    TOKEN_WORD, 
} token_type_t; //alias

typedef struct{ 
    token_type_t type;
    char* text;
} token_t;

//declare function to define each token, allow for separate compilation -- definition in source file
token_type_t classify_token(char* text); 
    //given a single token, return its type 
token_t* get_token_stream(FILE* stream); 
    //take input, split it into tokens, classify each token,and return a stream of tokens.

#endif // INT_TOKEN_H