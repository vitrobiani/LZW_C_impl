#include "lzw.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a string");
    }
    res* result = lzw(argv[1]);
    if (argc == 3 && strcmp("-d", argv[2])) {
        printf("The lzw coding dictionary: \n");
        printDict(result->d);
        printf("\n");
    }
    printf("The lzw coding: \n");
    printFromDict(result->d, result->msg, result->msgLen);

    res* r = lzw_decode(result->msg , result->msgLen);
    if (argc == 3 && strcmp("-d", argv[2])) {
        printf("\nThe lzw decoding dictionary: \n");
        printDict(r->d);
    }
    printf("\nThe lzw decoding: \n");
    printFromDict(r->d, r->msg, r->msgLen);

    return 1;
}
