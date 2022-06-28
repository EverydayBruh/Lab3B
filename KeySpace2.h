#ifndef KEYSPACE2_H
#define KEYSPACE2_H

#include "structs.h"

address newTable(int size, FILE* fb);
Table2 readTable(int pos, FILE* fb);
int addElement2(Table2 table, KeyType2 key, InfoType info, FILE* fb);
void printTable2(Table2 table, FILE* fb);
void printElement2(KeySpace2 element, FILE* fb);
void printInfo(InfoType info, FILE* fb);

Table2* getItems2(Table2 *table, KeyType2 key);
Table2* getItemByVer2(Table2 *table, KeyType2 key, RelType2 release);
//InfoType* getInfo2(Table2 *table, KeyType2 key);

void delByKey(Table2 table, KeyType2 key, FILE* fb);

// WORKING WITH FILE

int writeElement(KeySpace2 element, FILE* fb);
KeySpace2 readElement(int pos, FILE* fb);

address writeText(char* text, FILE* fb);
InfoType createInfoFromText(char* text, FILE* fb);

#endif