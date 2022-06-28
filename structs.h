#ifndef STRUCTS_H
#define STRUCTS_H

#include <ctype.h>


typedef int address;


typedef struct InfoType{
    int length;
    int text;
} InfoType;

typedef struct Item{
    int pos;
    int size;
} Item;



typedef int KeyType1;
typedef int KeyType2;
void clearKey(KeyType2* key);

typedef int PointerType1;
typedef int BusyType2;
typedef int RelType2;
typedef int SizeType1;
typedef int IndexType2;



typedef struct KeySpace2 {
int busy;     // признак занятости элемента
int key;
int release;   // номер версии элемента
InfoType info;
} KeySpace2;

typedef struct FileKeySpace2 {
Item busy;     // признак занятости элемента
Item key;
Item release;   // номер версии элемента
Item info;
} FileKeySpace2;

typedef struct Table2 {
int size;
address arr;
} Table2;






#endif