#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_SIZE 32
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

//der reh


//def free
void freeHT(HashTable* ht){
    for(int i = 0; i < ht->sizeHashTable; i++){
        free(ht->ht[i]->el);
        free(ht->ht[i]);
    }
    free(ht->ht);
}

//def initEl
int initList(char* str, List** ht, int sizeHashTable){
    int adrs = hashfunc(str, sizeHashTable);
    while (1){
        if (ht[adrs]->el==NULL){
            ht[adrs]->el = str;
            ht[adrs]->counter++;
            return 1;
        }else if(!strcmp(str, ht[adrs]->el)){
            ht[adrs]->counter++;
            return 0;
        }else{
            adrs = (adrs+1)%(sizeHashTable);
        }
    }
}

//reh
int rehash(HashTable* ht){
    
}

int initEl(char* str, HashTable* ht){
    int adrs = hashfunc(str, ht->sizeHashTable);
    ht->notempy+=initList(str, ht->ht, ht->sizeHashTable);
    if (ht->notempy/ht->sizeHashTable>=CRITICAL_PERSENT){
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
void printHashTable(HashTable* ht){
    for(int i = 0; i<ht->sizeHashTable;i++){
        if (ht->ht[i]->el!=NULL){
            printf("%2d: %s", i, (char*)(ht->ht[i]->el));
        }else
            printf("%2d: NULL\n", i);
    }
}

//def benchmarck

int main(int argc, char* argv[]){
    HashTable ht;
    createHashTable(&ht);
    FILE* file = fopen("text.txt", "r");
    input(&ht, file);
    printHashTable(&ht);
    printf("%d\n", ht.notempy);
    freeHT(&ht);
    fclose(file);
}
