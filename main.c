#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_SIZE 64

//struct list
typedef struct Zlist{
    void* el;
    int counter;
    struct Zlist* next;
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

//def creat
int createHashTable(HashTable* t){
    t->sizeHashTable=BASE_SIZE;
    t->notempy = 0;
    t->ht = calloc(sizeof(List*), t->sizeHashTable);
    
    for(int i = 0; i<BASE_SIZE;i++){
        t->ht[i] = malloc(sizeof(List));
        *(t->ht[i]) = (List){NULL, 0, NULL};
        if (i){
            t->ht[i-1]->next=t->ht[i];
        }
    }
}

//der reh

//def free

//def init
int conditions(char* str, HashTable* ht, int adrs){
    if (ht->ht[adrs]->el==NULL){
        ht->ht[adrs]->el = str;
        ht->ht[adrs]->counter++;
    }else if(!strcmp(str, ht->ht[adrs]->el)){
        ht->ht[adrs]->counter++;
    }else{
        conditions(str, ht, (adrs+1)%(ht->sizeHashTable));
    }
}

int init(char* str, HashTable* ht){
    int adrs = hashfunc(str, ht->sizeHashTable);
    conditions(str, ht, (adrs+1)%(ht->sizeHashTable));
}

//def search

//def del

//def input
void input(HashTable* ht, FILE* rsr){
    char arr[256];
    fscanf(rsr, "%s", arr);
}

//def output
void printHashTable(HashTable* ht){
    for(int i = 0; i<ht->sizeHashTable;i++){
        if (ht->ht[i]->el!=NULL){
            printf("%2d: %s\n", i, (char*)(ht->ht[i]->el));
        }else
            printf("%2d: NULL\n", i);
    }
}

//def benchmarck

int main(int argc, char* argv[]){
    HashTable ht;
    createHashTable(&ht);
    char arr[40];
    scanf("%s",arr);
    init(arr, &ht);
    printHashTable(&ht);
}
