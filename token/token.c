
#include "token.h" //"" in same directory
#include <ctype.h> //for isalpha, etc in classify
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strtok

token_type_t classify_token(char *text){ 
    int i; 
    int isNum = 1, isStr = 1, isOp = 1, isSym = 1; //assume true, set to false in loop

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
        return TOKEN_NUM;
    }else if (isStr){ 
        return TOKEN_STR; 
    }else if (isOp) {
        return TOKEN_OP;
    }else if (isSym){ 
        return TOKEN_SYM;
    }else{ //failing case (perhaps should make enum 0?)
        return TOKEN_UNKNOWN;
    }
}

//need to add something to ignore space characters following last token
    token_t* get_token_stream(FILE *stream){ 
        printf("Type Here: ");
        token_t* tokens = malloc(MAX_TOKENS * sizeof(token_t)); //array to be returned 
        int token_count = 0; 

        char *buffer = NULL; //hold the line of text read from the stream
        size_t buffsize = 0; //allocated by getline()
        char *typeName = "";

       if(getline(&buffer, &buffsize, stream) !=  -1){ //getline returns -1 when EOF
        char *currToken = strtok(buffer, " ");//split stream at each blank space -- " " delimiter
            while(currToken != NULL && token_count < MAX_TOKENS){ 
                token_type_t type = classify_token(currToken);

                //add to array to be returned (with value and type)
                tokens[token_count].type = type;
                tokens[token_count].text = strdup(currToken);  // Make sure to free this later!
                
                if (type == 0){ typeName = "Number";
                }else if (type == 1){ typeName = "Operation";                
                }else if (type == 2){ typeName = "Symbol";  
                }else if (type == 3){ typeName = "String"; 
                }else{ typeName = "Unknown";} 

                currToken[strcspn(currToken, "\n")] = 0;
                
                //printf("{Token: %s\t Type: %s}\n\n", currToken, typeName); //weird format on last currToken
                token_count++; 
                currToken = strtok(NULL, " ");//get next currToken
            }
       }
       free(buffer);
       return tokens;
    }