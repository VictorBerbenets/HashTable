#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "validator.h"
#include "list.h"

typedef struct {
    
List*  arr;
size_t size;

size_t (*HashFunction)( const char* );

} HashTable;

// size_t HashFunction( const char* data_string);

//------------------------------------------------------------------------//
HashTable CtorHashTable(size_t size);
const char* ReadText(const char* file_name);
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
void DtorHashTable(HashTable* hash_table);
void PushWordToHashTable(HashTable* hash_table, elem_t word);
void FillHashTable(HashTable* hash_table, const char* data_text);
void SkipSpaces(const char** text);
//------------------------------------------------------------------------//
size_t GetWorldLength(const char* buffer);
//------------------------------------------------------------------------//
long GetFileSize(const char *file);
//------------------------------------------------------------------------//

#endif