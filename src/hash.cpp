#include "include/hash.h"
#include <ctype.h>

//*********************************************************<Hash Table Functions>**********************************************************************
//----------------------------------------------------------------------------------------------------------------------------------------------------//
HashTable CtorHashTable(size_t size, size_t (*HashFunction)(const char*)) {

    HashTable hash_table = {};
    hash_table.arr  = (List*) calloc(size, sizeof(List));
    hash_table.size = size;
    Validator(hash_table.arr == nullptr, "calloc couldn't get memory", exit(MEM_ALLOCATED_ERR));

    for (size_t list_number = 0; list_number < size; ++list_number) {
        hash_table.arr[list_number] = ListCreate();
    }
    hash_table.HashFunction = HashFunction;
    return hash_table;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void FillHashTable(HashTable* hash_table, const char* data_text) {

    const char* buffer = ReadText(data_text);

    Validator(buffer == nullptr, "invalid pointer", return ;);
    char* save_buff_address = (char*)buffer;

    size_t word_len  = 0;
    int readed_symbs  = 0;
    char* word_ptr    = 0;

    int is_not_empty = 1;
    while(is_not_empty) {

        SkipTrash(&buffer);
        readed_symbs = 0;

        word_len = GetWorldLength(buffer);
        if (word_len) {
            word_ptr = CreateString(word_len);
            sscanf(buffer, "%[a-zA-Z]%n", word_ptr, &readed_symbs);
            buffer += readed_symbs;

            PushWordToHashTable(hash_table, word_ptr);
        }
        if (!readed_symbs || *buffer == '\0') {
            is_not_empty = 0;
        }
    }
    free(save_buff_address);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

char* CreateString(int word_len) {
    char* word_ptr = (char*) calloc(word_len + 1, sizeof(char));
    word_ptr[word_len] = '\0';
    return word_ptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

size_t GetWorldLength(const char* buffer) {
    size_t char_counter = 0;
    while (isalpha(buffer[char_counter])) {
        ++char_counter;
    }
    return char_counter;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

const char* ReadText(const char* file_name) {
    FILE* text = fopen(file_name, "r");
    Validator(text == nullptr, "in reading file", return nullptr);

    long buffer_size = GetFileSize(file_name);
    char* buffer = (char*) calloc(buffer_size + 1, sizeof(char));

    size_t is_fread_well_done = fread(buffer, buffer_size, sizeof(char), text);
    Validator(is_fread_well_done == 0, "you entered empty file or it was fread error", return nullptr);
    buffer[buffer_size] = '\0';

    int is_file_closed = fclose(text);
    Validator(is_file_closed != 0, "in closin file", return nullptr);

    return (const char*)buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void PushWordToHashTable(HashTable* hash_table, elem_t word) {
    Validator(word == nullptr, "invalid word pointer", return ;);
    
    if (FindHashData(hash_table, word)) {
        free((char*)word);
        return ;
    }

    size_t hash = hash_table->HashFunction(word) % hash_table->size;
    ListInsertHead(&(hash_table->arr[hash]), word);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//
int FindHashData(HashTable* hash_table, elem_t word) {
    size_t key     = hash_table->HashFunction(word);
    size_t cell_id = key % hash_table->size;

    Node* node_ptr = hash_table->arr[cell_id].head;
    for (int elem_number = 0; elem_number < hash_table->arr[cell_id].size; elem_number++, node_ptr = node_ptr->next) {
        if (node_ptr && !strcmp(word, node_ptr->value)) {
            return 1;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void DtorHashTable(HashTable* hash_table) {
    if (!hash_table) {
        printf("Can't delete hash table because of nullptr\n");
        return ;
    }

    for (size_t list_number = 0; list_number < hash_table->size; ++list_number) {

        ListDestructor(&hash_table->arr[list_number]);
    }

    free(hash_table->arr);
    hash_table->size = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void SkipTrash(const char** text) {
    Validator(*text == nullptr, "invalid string pointer", return ;);
    while(**text != '\0' && !isalpha(**text)) {
        (*text)++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void DeleteHashElement(HashTable* hash_table, const char* word) {
    size_t key     = hash_table->HashFunction(word);
    size_t cell_id = key % hash_table->size;

    Node* node_ptr = hash_table->arr[cell_id].head;
    for (int elem_number = 0; elem_number < hash_table->arr[cell_id].size; elem_number++, node_ptr = node_ptr->next) {
        if (node_ptr && !strcmp(word, node_ptr->value)) {
            if (node_ptr->value) {
                free((char*)node_ptr->value);
            }
            DeleteNode(&hash_table->arr[cell_id], elem_number + 1);
            return ;
        }
    }

    printf("Element to delete was not fined: %s\n", word);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------//

void HashTableDump(HashTable* hash_table, int line, const char* func_name, const char* file_name) {
    printf("\n*--------------------------------------------------------------------------------------------------*\n");
    printf("*-----------------------------------Hash Table Dump------------------------------------------------*\n");
    printf("***Hash table dump was called from:%s:%s:%d ***\n", file_name, func_name, line);
    printf("***Size: '%zd' ***\n", hash_table->size);
    printf("***DATA:\n\n");

    Node* list_ptr = nullptr; 
    for (size_t list_id = 0; list_id < hash_table->size; ++list_id) {
        list_ptr = hash_table->arr[list_id].head;
        for (size_t list_element = 0; list_element < (size_t)hash_table->arr[list_id].size; list_element++, list_ptr = list_ptr->next) {
            if (list_ptr->value) {
                printf("***[%zd][%zd] = '%s' ***\n", list_id, list_element, list_ptr->value);
            }
        }
    }
    printf("*----------------------------------------End Dump--------------------------------------------------*\n");
    printf("*--------------------------------------------------------------------------------------------------*\n\n");

}
//----------------------------------------------------------------------------------------------------------------------------------------------------//



//перестройка хэш таблицу