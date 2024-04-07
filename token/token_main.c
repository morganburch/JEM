#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "token.c"

int main(int argc, char** argv){
    get_token_stream(stdin); 
    return 0; 
}
