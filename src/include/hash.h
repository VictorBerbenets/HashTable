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
HashTable CtorHashTable(size_t size, size_t (*HashFunction)(const char*));
const char* ReadText(const char* file_name);
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
#define HashDump(hash_table) HashTableDump(&hash_table, __LINE__, __PRETTY_FUNCTION__, __FILE__)

void HashTableDump(HashTable* hash_table, int line, const char* func_name, const char* file_name);
void FillHashTable(HashTable* hash_table, const char* data_text);
void DeleteHashElement(HashTable* hash_table, const char* word);
void PushWordToHashTable(HashTable* hash_table, elem_t word);
void DtorHashTable(HashTable* hash_table);
void SkipTrash(const char** text);
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
size_t GetWorldLength(const char* buffer);
// --- hash funcs: ---
size_t WordLengthHash(const char* word);
size_t AsciiSumHash(elem_t word);

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
int FindHashData(HashTable* hash_table, elem_t word);
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
long GetFileSize(const char *file);
//------------------------------------------------------------------------//

#endif