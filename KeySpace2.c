#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "InOut.h"


IndexType2 hash(Table2 table, KeyType2 key, int i){
    return (key+i) % table.size;
}

void printInfo(InfoType info, FILE* fb){
    char* text = calloc(info.length+1, sizeof(char));
    // printInteger(info.text);
    fseek(fb, info.text, SEEK_SET);
    fread(text, sizeof(char), info.length+1, fb);
    // puts(text);
    
    // printf("%c ", text[999]);
    printf("%s ", text);
    free(text);
}

void printKey(KeyType2 key){
    printf("%d ", key);
}

void printVersion(RelType2 release){
    printf("%d ", release);
}

void printElement2(KeySpace2 element, FILE* fb){
    printf("Busy: ");
    printf("%d ", element.busy);
    if(element.busy == 1){
        printf("Info: ");
        printInfo(element.info, fb);
        printf("Key: %d ", element.key);
        printf("Version: ");
        printVersion(element.release);
    }
    printf("\n");
}

int writeElement(int pos, KeySpace2 element, FILE* fb){
    fseek(fb, pos, SEEK_SET);
    fwrite(&element, sizeof(element), 1, fb);
    return pos;
}

int writeElementByIndex(KeySpace2 element, Table2 table, int index, FILE* fb){
    int pos = ftell(fb);
    if(index >= table.size){
        printf("Too big index\n");
    }
    writeElement(table.arr + index*sizeof(KeySpace2), element, fb);
      
    return pos;
}

KeySpace2 readElement(int pos, FILE* fb){
    KeySpace2 element;
    fseek(fb, pos, SEEK_SET);
    fread(&element, sizeof(KeySpace2), 1, fb);
    // printf("Read element:");
    // printElement2(element, fb);
    return element;
}

address writeText(char* text, FILE* fb){
    // puts(text);
    address cur = ftell(fb);
    fseek(fb, 0, SEEK_END);
    address pos = ftell(fb);
    fwrite(text, sizeof(char), strlen(text)+1, fb);
    fseek(fb, cur, SEEK_SET);
    //  puts(text);
    // printInteger(cur);
    // printInteger(pos);
    return pos;
}

InfoType createInfoFromText(char* text, FILE* fb){
    InfoType info;
    info.length = strlen(text);
    info.text = writeText(text, fb);
    // printInteger(3);
    // puts(text);
    // printInfo(info, fb);
    return info;
}


address newTable(int size, FILE* fb){
    int pos = ftell(fb);
    Table2 table;
    table.size = size;
    KeySpace2 element;
    element.busy = 0;
    table.arr = ftell(fb) + sizeof(Table2);   
    int cur = table.arr;
    fwrite(&table, sizeof(Table2), 1, fb);
    for(int i = 0; i < size; i++){
        writeElement(cur, element, fb);
        cur += sizeof(KeySpace2);
    }
    printElement2(element, fb);
    return pos;
}

Table2 readTable(int pos, FILE* fb){
    Table2 table;
    fseek(fb, pos, SEEK_SET);
    fread(&table, sizeof(table), 1, fb);
    return table;
}






KeySpace2 getElementByIndex(Table2 table, int index, FILE* fb){
    if(index >= table.size){
        printf("Too big index\n");
    }
    KeySpace2 element = readElement(table.arr + index*sizeof(KeySpace2), fb);
    // printf("Get element by Index:");
    // printElement2(element, fb);
    return element;
}

void printTable2(Table2 table, FILE* fb){
    address pos = table.arr;
    KeySpace2 element;
    for(int i = 0; i < table.size; i++){
        element = getElementByIndex(table, i, fb);
        printElement2(element, fb);
    }
}

int addElement2(Table2 table, KeyType2 key, InfoType info, FILE* fb){
    address arr = table.arr;
    int index;
    RelType2 rel = 0;
    KeySpace2 element;

    for(int i = 0; i < table.size; i++){
        index = hash(table, key, i);
        element = getElementByIndex(table, index, fb);
        if(element.busy == 0){
            element.busy = 1;
            element.key = key;
            element.info = info;
            element.release = rel;
            //fseek(fb, )
            writeElementByIndex(element, table, index, fb);
            // printElement2(element, fb);
            printf("Index: %d\n", index);
            printElement2(getElementByIndex(table, index, fb), fb);
            // printf("Key: %d", element.key);
            
            printf("Succes!\n");
            return 0;
        } else if (element.key == key){
            rel = element.release + 1;
        }
    }
    return -1;
}

void delByKey(Table2 table, KeyType2 key, FILE* fb){
    int index;
    KeySpace2 element;
    for(int i = 0; i < table.size; i++){
        index = hash(table, key, i);
        element = getElementByIndex(table, index, fb);
        if(element.busy == 1 && element.key == key){
            element.busy = 0;
            writeElementByIndex(element, table, index, fb);
            printf("Deleted!\n");
        }
    }
}
