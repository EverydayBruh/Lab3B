#ifndef KEYSPACE2_H
#define KEYSPACE2_H

#include "structs.h"

Table2* newTable(int size);
int addElement2(Table2 *table, KeyType2 key, InfoType* info);
void printTable2(Table2 *table);

Table2* getItems2(Table2 *table, KeyType2 key);
Table2* getItemByVer2(Table2 *table, KeyType2 key, RelType2 release);
//InfoType* getInfo2(Table2 *table, KeyType2 key);
void delTable2(Table2 *table);
void delByKey2(Table2 *table, KeyType2 key);




#endif