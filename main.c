#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "InOut.h"
#include "KeySpace2.h"

InfoType* readInfo(){
    InfoType* info = malloc(sizeof(InfoType));
    info->text = read_line();
    return info;
}

int addElement(Table2* table){
    printf("Info: ");
    InfoType* info = readInfo();
    printf("Key: ");
    KeyType2 key;
    readint(&key);
    if(addElement2(table, key, info) == 0){
        return 0;
    } else {
        printf("Array is full! \n");
        return -1;
    }
}

int readTable(Table2* table2){
    int i = 0;
    while(table2->size>i){
        if(addElement(table2) != 0){
            return 1;
        }
        i++;
    }
    return 0;
}

int main(){
    int size2;
    printf("Enter table size: ");
    readPositive(&size2);
    Table2* table2 = newTable(size2);
    Table2* newTable2;
    KeyType2 key;
    char* s;
    
    int switcher = 1;
    while(switcher!=6){
        printf("\n\n1. Add element \n2. Find by key \n3. Find by key and release \n4. Delete element \n5. Print Table \n6. Exit\n");
        readPositive(&switcher);
        printf("\n");

        switch(switcher){
            case 1:
                if(addElement(table2) != 0){
                    //ошибка
                }
                break;
            
            case 2:
                printf("Enter key:   ");
                readint(&key);
                newTable2 = getItems2(table2, key);
                printTable2(newTable2);
                delTable2(newTable2);
                break;
            
            case 3:
                printf("Enter key:   ");
                readint(&key);
                RelType2 release;
                printf("Enter release:   ");
                readint(&release);
                newTable2 = getItemByVer2(table2, key, release);
                printTable2(newTable2);
                delTable2(newTable2);
                break;

            case 4:
                printf("Enter key:   ");
                readint(&key);
                delByKey2(table2, key);
                
                break;

            case 5:
                printTable2(table2);
                break;

            case 6:
                break;

            default:
                printf("Incorrect value\n");
                break;


        }
    }
    delTable2(table2);
    return 0;
}