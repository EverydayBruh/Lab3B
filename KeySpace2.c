#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


void clearTable2(Table2* table){
    for(int i = 0; i < table->size; i++){
        table->arr->busy = 0;
    }
}

void copyElement2(KeySpace2* source, KeySpace2* dest){
    dest->busy = source->busy;
    dest->key = source->key;
    dest->release = source->release;
    // printf("Info copy");
    dest->info = malloc(sizeof(InfoType));
    copyInfo(source->info, dest->info);
}

Table2* newTable(int size){
    Table2* table = malloc(sizeof(Table2));
    table->size = size;
    table->arr = calloc(size, sizeof(KeySpace2));
    clearTable2(table);
    return table;
}

void printInfo(InfoType* info){
    printf("%s ", info->text);
}

void printKey(KeyType2 key){
    printf("%d ", key);
}

void printVersion(RelType2 release){
    printf("%d ", release);
}


void printElement2(KeySpace2* element){
    printf("%d ", element->busy);
    if(element->busy == 1){
        printInfo(element->info);
        printKey(element->key);
        printVersion(element->release);
    }
}

void printTable2(Table2* table){
    for(int i = 0; i < table->size; i++){
        printElement2(&(table->arr[i]));
        printf("\n");
    }
}

IndexType2 hash(Table2 *table, KeyType2 key, int i){
    return (key+i) % table->size;
}

int addElement2(Table2 *table, KeyType2 key, InfoType* info){
    IndexType2 index;
    KeySpace2* arr = table->arr;
    RelType2 rel = 0;

    for(int i = 0; i < table->size; i++){
        index = hash(table, key, i);
        if(arr[index].busy == 0){
            arr[index].busy = 1;
            arr[index].key = key;
            arr[index].info = info;
            arr[index].release = rel;
            printf("Succes!\n");
            return 0;
        } else if (arr[index].key == key){
            rel = arr[index].release + 1;
        }
    }
    return -1;
}

Table2* getItemByVer2(Table2 *table, KeyType2 key, RelType2 release){
    //FIND BY KEY ONLY -> release = -1
    // printf("getItems2 Start\n");

    IndexType2 index;
    Table2* newTable = malloc(sizeof(Table2));
    newTable->size = 0;
    KeySpace2* arr = table->arr;
    int i = 0;

    for(i = 0; i < table->size; i++){
        index = hash(table, key, i);
        if(arr[index].busy == 1){
            if(arr[index].key == key && (release == -1 || release == arr[index].release)){
                newTable->size++;
                if(newTable->size==1){
                    newTable->arr = malloc(sizeof(KeySpace2));
                } else {
                    newTable->arr = realloc(newTable->arr, newTable->size * sizeof(KeySpace2));
                }
                copyElement2( &(arr[index]), &(newTable->arr[newTable->size-1]) );
                
            }
        } 
    }
    return newTable;
}

int freeElement2(KeySpace2* element){
    if(element == NULL){return 1;}
    if(element->busy == 0){return 0;}
    if(element->info!=NULL){
        clearInfo(element->info);
        
    }
    element->busy = 0;
    clearKey(&(element->key));
    return 0;
}

void delByKey2(Table2 *table, KeyType2 key){
    KeySpace2* arr = table->arr;
    int i = 0;
    int index;

    for(i = 0; i < table->size; i++){
        index = hash(table, key, i);
        if(arr[index].busy == 1){
            if(arr[index].key == key){
               freeElement2(&(arr[index]));
            }
        } 
    }
    
}

int delTable2(Table2* table){
    if(table == NULL){
        return 1;
    }
    KeySpace2* arr = table->arr;
    for(int i = 0; i<table->size; i++){
        freeElement2(&(arr[i]));
    }
    free(arr);
    free(table);
    return 0;
}

Table2* getItems2(Table2 *table, KeyType2 key){
    Table2* newTable =  getItemByVer2(table, key, -1);
    return newTable;
    
}