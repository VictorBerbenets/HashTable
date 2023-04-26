#ifndef LISTIK_H
#define LISTIK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validator.h"
#include "colors.h"
#include "Graph.h"

#define PrintFuncPosition() fprintf(stderr, "%s was called from:\n" White " %s:%s:%d\n" Gray "", __PRETTY_FUNCTION__, file, func, line)
#define ListDump(list) _ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__)

typedef const char* elem_t;
const int Max_Dot_Command_Len = 150;

/// list structers///
typedef struct Node Node;

struct Node{

    elem_t value = 0;
    Node* next;
    Node* prev;
} ;

typedef struct {

    Node* tail;
    Node* head;
    int size;
    int Dump_Number;
} List;
/////////////////////

enum List_params {

    Poison             = 0XDEADBABE,
    INSERT_TAIL        = 0xDEDFEED1,
    INSERT_HEAD        = 0xDEDFEED2,
    DELETE_TAIL        = 111,
    DELETE_Head        = 112,
    DELETE_LAST_NODE   = 113,
    VALUE_NOT_FOUND    = -1,
    ListInitSize       = 0,
    Logic_Head         = 1,
    One_Node           = 1,
};

enum ListErrors {

    MEM_ALLOCATED_ERR   = 5353535, 
    INVALID_LOGIC_ID    = 0XFEEDFAC1,
    INVALID_NODE_ID     = 0XFEEDFAC2,
    CLOSE_FILE_ERROR    = 0XDEADFEED,
    OPEN_FILE_ERROR     = 0XDEADBABE,
} ;

#endif

List ListCreate();

void InsertFirstNode(List* list, Node* new_node, elem_t value);

int ListInsertTail(List* list, elem_t value);

int ListInsertHead(List* list, elem_t value);

int ListInsertRight(List* list, elem_t value, int logic_id);

int ListInsertLeft(List* list, elem_t value, int logic_id);

void InsertNode(List* list, elem_t value, int logic_id);

Node* GetIdByOptimalWay(List* list, int logic_id);

elem_t GetListValue(List* list, int logic_id);

int FindFirstListValue(List* list, elem_t value);

int DeleteNode(List* list, int logic_id);

void DeleteLastNode(List* list);

void DeleteTail(List* list);

void DeleteHead(List* list);

void ListDestructor(List* list);

void _ListDump(List* list, const char* file, const char* func, int line);

int ListGraph(List *list);