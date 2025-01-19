#include "lzw.h"

res* lzw(char* msg) {
    res* r = malloc(sizeof(res));
    r->msgLen = 0;
    int* send = malloc(sizeof(int)*MAX_STR_LEN);
    int cur = 0;
    dict* d = malloc(sizeof(dict));
    d->pairs = malloc(sizeof(pair*));
    if (d->pairs == NULL) exit(42);
    d->pairs = NULL;
    initDict(d);
    d->cur = 255;
    int len = strlen(msg);

    char* p = malloc(sizeof(char)*MAX_STR_LEN);
    p[0] = msg[0];
    p[1] = '\0';
    for (int i = 0; i < len+1; i++) {
        char c[2] = {msg[i+1], '\0'};
        char* pc = strdup(p);
        strcat(pc, c);
        if(isInDict(d, pc)){
            strcpy(p, pc);
        } else{
            send[cur++] = getId(d, p);
            r->msgLen++;
            addToDict(d, pc);
            p = strdup(c);
        }
    }
    r->d = d;
    r->msg = send;

    return r;
}

res* lzw_decode(int* msg, int len) {
    res* r = malloc(sizeof(res));
    r->msgLen = 0;

    dict* d = malloc(sizeof(dict));
    if (d == NULL) exit(42);
    d->pairs = NULL;
    initDict(d);
    d->cur = 255;

    int* decoded = malloc(sizeof(int) * MAX_STR_LEN);
    if (decoded == NULL) exit(42);
    int cur = 0;

    char* prev = getData(d, msg[0]);
    if (prev == NULL) exit(42);

    for (int i = 0; i < (int) strlen(prev); i++) {
        decoded[cur++] = prev[i];
        r->msgLen++;
    }

    for (int i = 1; i < len; i++) {
        char* entry = getData(d, msg[i]);
        char* newEntry;

        if (entry == NULL) {
            entry = malloc(strlen(prev) + 2);
            if (entry == NULL) exit(42);
            strcpy(entry, prev);
            entry[strlen(prev)] = prev[0];
            entry[strlen(prev) + 1] = '\0';
        }

        for (int j = 0; j < (int) strlen(entry); j++) {
            decoded[cur++] = entry[j];
            r->msgLen++;
        }

        newEntry = malloc(strlen(prev) + 2);
        if (newEntry == NULL) exit(42);
        strcpy(newEntry, prev);
        newEntry[strlen(prev)] = entry[0];
        newEntry[strlen(prev) + 1] = '\0';

        addToDict(d, newEntry);

        prev = strdup(entry);

        if (msg[i] >= d->cur) {
            free(entry);
        }
    }

    free(prev);

    r->msg = decoded;
    r->d = d;
    return r;
}

char* getDynStr(char* str) {
  char* theStr;
  theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
  if (!theStr)
    return NULL;

  strcpy(theStr, str);
  return theStr;
}

int isInDict(dict* d, char* str) {
    for (int i = 0 ; i < d->len; i++) {
        if (strcmp(d->pairs[i].data, str) == 0) {
            return 1;
        }
    }
    return 0;
}

void printFromDict(dict* d, int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d = %s\n", arr[i], getData(d, arr[i]));
    }
}

void addToDict(dict* d, char* str) {
    pair* pairs = realloc(d->pairs, sizeof(pair) * (d->len + 1));
    if (pairs == NULL) { exit(42);}
    d->pairs = pairs; 
    d->pairs[d->len].data = getDynStr(str);
    if (d->pairs[d->len].data == NULL) { exit(42);}
    d->pairs[d->len].id = ++d->cur; 
    d->len++;
}

void printDict(dict* d) {
    for (int i = 0; i < d->len; i++) {
        printf("str: %s, id: %d\n", d->pairs[i].data, d->pairs[i].id);
    }
}

char* getData(dict* d, int id) {
    for (int i = 0 ; i < d->len; i++) {
        if (d->pairs[i].id == id) {
            return d->pairs[i].data;
        }
    }
    return NULL;
}

int getId(dict* d, char* str) {
    for (int i = 0 ; i < d->len; i++) {
        if (strcmp(d->pairs[i].data, str) == 0) {
            return d->pairs[i].id;
        }
    }
    return 0;
}

void addToDictWithId(dict* d, char* str, int id){
    pair* pairs = realloc(d->pairs, sizeof(pair) * (d->len + 1));
    if (pairs == NULL) { exit(42);}
    d->pairs = pairs; 
    d->pairs[d->len].data = getDynStr(str);
    if (d->pairs[d->len].data == NULL) { exit(42);}
    d->pairs[d->len].id = id; 
    d->len++;
}

void initDict(dict* d) {
    addToDictWithId(d, "A", 65);
    addToDictWithId(d, "B", 66);
    addToDictWithId(d, "C", 67);
    addToDictWithId(d, "D", 68);
    addToDictWithId(d, "E", 69);
    addToDictWithId(d, "F", 70);
    addToDictWithId(d, "G", 71);
    addToDictWithId(d, "H", 72);
    addToDictWithId(d, "I", 73);
    addToDictWithId(d, "J", 74);
    addToDictWithId(d, "K", 75);
    addToDictWithId(d, "L", 76);
    addToDictWithId(d, "M", 77);
    addToDictWithId(d, "N", 78);
    addToDictWithId(d, "O", 79);
    addToDictWithId(d, "P", 80);
    addToDictWithId(d, "Q", 81);
    addToDictWithId(d, "R", 82);
    addToDictWithId(d, "S", 83);
    addToDictWithId(d, "T", 84);
    addToDictWithId(d, "U", 85);
    addToDictWithId(d, "V", 86);
    addToDictWithId(d, "W", 87);
    addToDictWithId(d, "X", 88);
    addToDictWithId(d, "Y", 89);
    addToDictWithId(d, "Z", 90);

    addToDictWithId(d, "a", 97);
    addToDictWithId(d, "b", 98);
    addToDictWithId(d, "c", 99);
    addToDictWithId(d, "d", 100);
    addToDictWithId(d, "e", 101);
    addToDictWithId(d, "f", 102);
    addToDictWithId(d, "g", 103);
    addToDictWithId(d, "h", 104);
    addToDictWithId(d, "i", 105);
    addToDictWithId(d, "j", 106);
    addToDictWithId(d, "k", 107);
    addToDictWithId(d, "l", 108);
    addToDictWithId(d, "m", 109);
    addToDictWithId(d, "n", 110);
    addToDictWithId(d, "o", 111);
    addToDictWithId(d, "p", 112);
    addToDictWithId(d, "q", 113);
    addToDictWithId(d, "r", 114);
    addToDictWithId(d, "s", 115);
    addToDictWithId(d, "t", 116);
    addToDictWithId(d, "u", 117);
    addToDictWithId(d, "v", 118);
    addToDictWithId(d, "w", 119);
    addToDictWithId(d, "x", 120);
    addToDictWithId(d, "y", 121);
    addToDictWithId(d, "z", 122);
}
