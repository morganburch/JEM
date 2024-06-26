
#include "token.h" //"" in same directory
#include <ctype.h> //for isalpha, etc in classify
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strtok
#define TOKEN_EMPTY -1

token_t classify_token(char *text){ 
    int i; 
    int isNum = 1, isStr = 1, isOp = 1, isSym = 1; //assume true, set to false in loop
    token_t token;

    for (i = 0; i < strlen(text); i++) {
        if (!isspace(text[i])) {
            break;
        }
    }
    if (i == strlen(text)) { // If the token is all whitespace
        token.type = TOKEN_EMPTY;
        token.text = text;
        return token;
    }
    for(i=0; i < strlen(text); i++){ 
        if (text[i] == '\n') continue; //ignore newline bc strtok automatically adds one
        if (!isalpha(text[i])){ 
            isStr = 0;
        }if(!isdigit(text[i])){
             isNum = 0; 
        }if(!strchr("+-*/", text[i])){ 
            isOp = 0;             
        }if(!strchr(":,;", text[i])){
            isSym = 0; 
        }
    }
    //return the true flag 
    if(isNum){ 
        token.type = TOKEN_NUM;
    }else if (isStr){ 
        token.type = TOKEN_STR; 
    }else if (isOp) {
        token.type = TOKEN_OP;
    }else if (isSym){ 
        token.type = TOKEN_SYM;
    }else{ //failing case (perhaps should make enum 0?)
        token.type = TOKEN_UNKNOWN;
    }

    token.text = text;
    return token;
}

token_t* get_token_stream(FILE *stream) { 
    printf("Type Here: ");
    token_t* tokens = malloc(MAX_TOKENS * sizeof(token_t)); // array to be returned 
    int token_count = 0; 

    char *buffer = NULL; // hold the line of text read from the stream
    size_t buffsize = 0; // allocated by getline()

    while (getline(&buffer, &buffsize, stream) != -1) { // getline returns -1 when EOF
        buffer = realloc(buffer, buffsize + 2);
        strcat(buffer, " "); //add whitespace to the end of input string so strtok recognizes last token

        char *currToken = strtok(buffer, " "); // split stream at each blank space -- " " delimiter
        if(strcmp(currToken, "stop") == 0) {
                free(buffer);
                return tokens;
        }
        
        while (currToken != NULL && token_count < MAX_TOKENS) { 
            char *tokenText = malloc((strlen(currToken) + 1) * sizeof(char));
            strcpy(tokenText, currToken);
            
            token_t token = classify_token(tokenText);

             if (token.type == TOKEN_EMPTY) {
            free(tokenText);
            currToken = strtok(NULL, " ");
            continue;
        }
            // trim trailing spaces from the current token
            size_t len = strlen(token.text);
            while (len > 0 && isspace(currToken[len - 1])) {
                currToken[--len] = '\0';
            }

            // add to array to be returned (with value and type)
            tokens[token_count] = token;
                
            //printf("{Token: %s\t Type: %d}\n\n", token.text, token.type);  //weird format on last currToken
            token_count++; 
            currToken = strtok(NULL, " "); // get next currToken
        }

        buffer = NULL;
        buffsize = 0;

        // Return the token stream after processing each line
        return tokens;
    }

    // Free the buffer if no input is received
    free(buffer);
    return tokens;
}
