#ifndef STRUCTS_H
#define STRUCTS_H

#include <ctype.h>

typedef struct InfoType{
    char* text;
} InfoType;

int copyInfo(InfoType* source, InfoType* dest);
void clearInfo(InfoType* info);

typedef int KeyType1;
typedef int KeyType2;
void clearKey(KeyType2* key);

typedef int PointerType1;
typedef int BusyType2;
typedef int RelType2;
typedef int SizeType1;
typedef int IndexType2;

typedef struct Item {
// указатель на информацию
InfoType *info;

// ключ элемента из 1­го пространства ключей
KeyType1 key1;
// ключ элемента из 2­го пространства ключей
KeyType2 key2;

// связь с элементом 2­го пространства ключей по индексу
IndexType2 ind2;
// связь с элементом 1­го пространства ключей по указателю
PointerType1 *p1;
} Item;

typedef struct KeySpace1 {
KeyType1 key;   // ненулевой ключ элемента
KeyType1 par;   // ключ родительского элемента, может быть нулевым
Item *info;
struct KeySpace1 *next;
}KeySpace1;

typedef struct KeySpace2 {
BusyType2 busy;     // признак занятости элемента
KeyType2 key;
RelType2 release;   // номер версии элемента
InfoType *info;
} KeySpace2;

typedef struct Table2 {
int size;
KeySpace2* arr;
} Table2;



struct Table {
// указатель на первое пространство ключей
KeySpace1 *ks1;
// указатель на второе пространство ключей
KeySpace2 *ks2;
// количество элементов в области первого пространства ключей
SizeType1 csize1;
// размер области второго пространства ключей
IndexType2 msize2;
};


#endif