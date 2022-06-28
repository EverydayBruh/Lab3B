#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "InOut.h"
#include "KeySpace2.h"

InfoType readInfo(FILE* fb){
    char* text = read_line();
    InfoType info;
    info = createInfoFromText(text, fb);
    return info;
}

int addElement(Table2 table, FILE* fb){
    printf("Info: ");
    InfoType info = readInfo(fb);
    printf("Key: ");
    KeyType2 key;
    readint(&key);
    if(addElement2(table, key, info, fb) == 0){
        return 0;
    } else {
        printf("Array is full! \n");
        return -1;
    }
}



int main(){
    int size;
    KeyType2 key;
    Table2 table;
    address tableAddress;    
    KeySpace2 element;
    char* text = "Hello";
    char* s;
    char *filename = "database.bin";
    FILE* fb = fopen(filename, "r+b");
    if (fb == NULL){
        fb = fopen(filename, "w+b");
        fseek(fb, 0, SEEK_SET);
        printf("Enter table size: ");
        readPositive(&size);
        tableAddress = newTable(size, fb);
   
    } else {
        tableAddress = ftell(fb);
    }
    table = readTable(tableAddress, fb);
 
    int switcher = 1;
    while(switcher!=6){
        printf("\n\n1. Add element \n2. Find by key \n3. Find by key and release \n4. Delete element \n5. Print Table \n6. Exit\n");
        readPositive(&switcher);
        printf("\n");

        switch(switcher){
            case 1:
                if(addElement(table, fb) != 0){
                    //ошибка
                }
                break;
            
            case 2:
                printf("Enter key:   ");
                readint(&key);
                // newTable2 = getItems2(table2, key);
                // printTable2(newTable2);
                // delTable2(newTable2);
                break;
            
            case 3:
                printf("Enter key:   ");
                readint(&key);
                RelType2 release;
                printf("Enter release:   ");
                readint(&release);
                // newTable2 = getItemByVer2(table2, key, release);
                // printTable2(newTable2);
                // delTable2(newTable2);
                break;

            case 4:
                printf("Enter key:   ");
                readint(&key);
                delByKey(table, key, fb);
                
                break;

            case 5:
                printTable2(table, fb);
                break;

            case 6:
                break;

            default:
                printf("Incorrect value\n");
                break;


        }
    }
    
    //addElement(table, fb);
    delByKey(table, 1, fb);
    printTable2(table, fb);
    return 0;
}