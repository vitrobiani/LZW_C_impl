#ifndef LZW
#define LZW
#define MAX_STR_LEN 255
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair {
    char* data;
    int id;
}pair;

typedef struct dict{
    pair* pairs;
    int len;
    int cur;
}dict;

typedef struct res{
    int* msg;
    dict* d;
    int msgLen;
}res;

    res* lzw(char* msg);

    res* lzw_decode(int* msg, int len);

    void addToDict(dict* d, char* str);

    int isInDict(dict* d, char* str);

    void printDict(dict* d);

    void initDict(dict* d);

    void addToDictWithId(dict* d, char* str, int id);

    char* getData(dict* d, int id);

    void printFromDict(dict* d, int* arr, int len);

    char* getDynStr(char* str);

    int getId(dict* d, char* str);
#endif // !LZW
