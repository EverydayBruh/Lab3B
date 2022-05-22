#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

int copyInfo(InfoType* source, InfoType* dest){
    dest->text = calloc(strlen(source->text)+1, sizeof(char));
    strcpy(dest->text, source->text);
    // printf("%s\n", dest->text);
    return 0;
}

void clearInfo(InfoType* info){
    free(info->text);
    free(info);
    
}
void clearKey(KeyType2* key){
   
    
}