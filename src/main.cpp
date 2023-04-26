#include "include/hash.h"

int main(int argc, const char** argv) {

    if (argc > 2) {
        printf("too many command line arguments: %d. There can be only one - file name\n", argc);
        exit(EXIT_FAILURE);
    }

    HashTable hash_table = CtorHashTable(1001, HashFunction);

    FillHashTable(&hash_table, argv[1]);
    printf("data = <%s>\n", FindHashData(&hash_table, "he"));
    DtorHashTable(&hash_table);
    return 0;
}