#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_SIZE 8
#define CRITICAL_PERSENT 0.7

//struct list
typedef struct Zlist{
    void* el;
    int counter;
    //struct Zlist* next;
}List;

//struct ht
typedef struct ZHashTable{
    int sizeHashTable;
    int notempy;
    List** ht;
}HashTable;

void printList(List** ht, int sizeHashTable);

//def hash
size_t hashfunc(char* key, size_t htsize) {
	size_t h = 0x73f8e5a39fe37a1b;
	while(*key) {
		h ^= h << 13 | h >> 51;
		h += (*key)*0xa5a15f11a1f1af31;
		h = h << 49 | h>>15;
		key++;
	}
	return h % htsize;
}


List** createList(int size){
    List** ht = calloc(sizeof(List*), size);
    for(int i = 0; i<size;i++){
        ht[i] = malloc(sizeof(List));
        *(ht[i]) = (List){NULL, 0};
    }
    return ht;
}

//def creat
int createHashTable(HashTable* t){
    t->sizeHashTable=BASE_SIZE;
    t->notempy = 0;
    t->ht = createList(t->sizeHashTable);
}


//def free
void freeHT(HashTable* ht){
    for(int i = 0; i < ht->sizeHashTable; i++){
        free(ht->ht[i]->el);
    }
    free(ht->ht);
}

//def initEl
int initList(char* str, List** ht, int sizeHashTable, int num){
    int adrs = hashfunc(str, sizeHashTable);
    while (1){
        if (ht[adrs]->el==NULL){
            ht[adrs]->el = str;
            ht[adrs]->counter+=num;
            return 1;
        }else if(!strcmp(str, ht[adrs]->el)){
            ht[adrs]->counter+=num;
            return 0;
        }else{
            adrs = (adrs+1)%(sizeHashTable);
        }
    }
}

//reh
int rehash(HashTable* ht){
    int newSize = ht->sizeHashTable * 2;
    List** newLst = createList(newSize);
    //printList(newLst, newSize);
    //printf("eee\n");

    for(int i = 0; i < ht->sizeHashTable; i++){
        if(ht->ht[i]->el==NULL) continue;
        initList(ht->ht[i]->el, newLst, newSize, ht->ht[i]->counter);
    }
    //printf("eee\n\n\n\n");

    ht->ht = newLst;
    ht->sizeHashTable = newSize;
}

int initEl(char* str, HashTable* ht){
    int adrs = hashfunc(str, ht->sizeHashTable);
    ht->notempy+=initList(str, ht->ht, ht->sizeHashTable, 1);
    if ((float)(ht->notempy)/ht->sizeHashTable>CRITICAL_PERSENT){
        rehash(ht);
    }
}

//def search

//def del

//def input
void input(HashTable* ht, FILE* rsr){
    char inputStr[256];
    while (fgets(inputStr, 256, rsr)){
        char* str = calloc(sizeof(char), 256);
        strcpy(str, inputStr);
        initEl(str, ht);
    }
}

//def output
void printList(List** ht, int sizeHashTable){
    for(int i = 0; i<sizeHashTable;i++){
        if (ht[i]->el!=NULL){
            printf("%2d: %s", i, (char*)(ht[i]->el));
        }else
            printf("%2d: NULL\n", i);
    }
}

void printHashTable(HashTable* ht){
    printList(ht->ht, ht->sizeHashTable);
}

//def benchmarck

int main(int argc, char* argv[]){
    HashTable ht;
    createHashTable(&ht);
    FILE* file = fopen("text.txt", "r");
    input(&ht, file);
    printHashTable(&ht);
    freeHT(&ht);
    fclose(file);
}
