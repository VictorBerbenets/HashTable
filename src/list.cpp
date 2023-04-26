#include "include/hash.h"

List ListCreate() {

    List list = {};
    list.size = 0;

    list.head = nullptr;
    list.tail = nullptr;
    
    return list;
}

int ListInsertTail(List* list, elem_t value) {
    
    Node* new_tail = (Node*) calloc(One_Node, sizeof(Node));
    Validator(new_tail == nullptr, "in calloc: could not give memory", return MEM_ALLOCATED_ERR);

    if (list->size == ListInitSize) {

        InsertFirstNode(list, new_tail, value);
        return 0;
    }
    new_tail->prev   = list->tail;
    list->tail->next = new_tail;

    list->tail = new_tail;
    list->tail->value = value;
    list->tail->next  = nullptr;

    list->size++;
    return 0;
}

int ListInsertHead(List* list, elem_t value) {

    Node* new_head = (Node*) calloc(One_Node, sizeof(Node));
    Validator(new_head == nullptr, "in calloc: could not give memory", return MEM_ALLOCATED_ERR);

    if (list->size == ListInitSize) {

        InsertFirstNode(list, new_head, value);
        return 0;
    }

    new_head->next   = list->head;
    list->head->prev = new_head;

    list->head = new_head;
    list->head->value = value;
    list->head->prev  = nullptr;

    list->size++;
    return 0;
}

void InsertFirstNode(List* list, Node* new_node, elem_t value) {

        list->tail = new_node;
        list->head = new_node;
        list->head->value = value;
        list->head->next  = nullptr;
        list->head->prev  = nullptr;
        list->size++;
}

int ListInsertRight(List* list, elem_t value, int logic_id) {

    if (logic_id == list->size) {
        ListInsertTail(list, value);
        return INSERT_TAIL;
    }
    if (logic_id < 1 || logic_id > list->size) {
        fprintf(stderr, "invalid logic id: %d\n", logic_id);
        return INVALID_LOGIC_ID;
    }

    InsertNode(list, value, logic_id);
    return 0;
}

// This func inserts new node only with ride side of the logic node
void InsertNode(List* list, elem_t value, int logic_id) {

    Node* curr_node_ptr = GetIdByOptimalWay(list, logic_id);
    Node* next_node     = curr_node_ptr->next;

    Node* new_node = (Node*) calloc(One_Node, sizeof(Node));
    Validator(new_node == nullptr, "in calloc: could not give memory", return ;);

    new_node->next  = next_node;
    new_node->prev  = curr_node_ptr;
    next_node->prev = new_node;
    curr_node_ptr->next = new_node;
    new_node->value     = value;

    list->size++;
}

int ListInsertLeft(List* list, elem_t value, int logic_id) {

    if (logic_id == (ListInitSize + 1)) {
        ListInsertHead(list, value);
        return INSERT_HEAD;
    }

    if (logic_id < 1 || logic_id > list->size) {
        fprintf(stderr, "invalid logic id: %d\n", logic_id);
        return INVALID_LOGIC_ID;
    }

    InsertNode(list, value, logic_id - 1);
    return 0;
}

int DeleteNode(List* list, int logic_id) {

    if (logic_id < 1 || logic_id > list->size) {
        fprintf(stderr, "invalid logic id: %d\n", logic_id);
        return INVALID_LOGIC_ID;
    }
    if (list->size == One_Node) {
        DeleteLastNode(list);
        return DELETE_LAST_NODE;
    }
    if (logic_id == list->size) {
        DeleteTail(list);
        return DELETE_TAIL;
    }
    if (logic_id == Logic_Head) {
        DeleteHead(list);
        return DELETE_Head;
    }
    Node* node_to_del = GetIdByOptimalWay(list, logic_id);

    node_to_del->prev->next = node_to_del->next;
    node_to_del->next->prev = node_to_del->prev;

    free(node_to_del);
    list->size--;

    return list->size;
}

void DeleteLastNode(List* list) {

    list->head->value = nullptr;
    list->head->prev  = nullptr;
    list->head->next  = nullptr;
    list->size--;
}

void DeleteTail(List* list) {

    Node* left_neighbour = list->tail->prev;
    left_neighbour->next = nullptr;
    free(list->tail);
    list->tail = left_neighbour;
    list->size--;
}

void DeleteHead(List* list) {

    Node* right_neighbour = list->head->next;
    right_neighbour->prev = nullptr;
    free(list->head);
    list->head = right_neighbour;
    list->size--;
}

Node* GetIdByOptimalWay(List* list, int logic_id) {

    int path_length = 0;
    Node* curr_node_ptr = nullptr;
    if (logic_id >= list->size/2) {   
        path_length   = list->size - logic_id; 
        curr_node_ptr = list->tail;
        for (int node_counter = 0; node_counter < path_length; node_counter++) {
            curr_node_ptr = curr_node_ptr->prev;
        }
    }
    else {
        path_length   = logic_id;
        curr_node_ptr = list->head;
        for (int node_counter = 0; node_counter < path_length; node_counter++) {
            curr_node_ptr = curr_node_ptr->next;
        }
    }

    return curr_node_ptr;
}

int FindFirstListValue(List* list, elem_t value) {

    Node* node_ptr   = list->head;
    int current_node = 0;

    for (current_node = 1; current_node < list->size; current_node++, node_ptr = node_ptr->next) {
        if (node_ptr->value == value) {
            return current_node;
        }
    }
    return VALUE_NOT_FOUND;
}

elem_t GetListValue(List* list, int logic_id) { //return status

    if (logic_id < 1 || logic_id > list->size) {
        fprintf(stderr, "invalid logic id: %d\n", logic_id);
        return nullptr;
    }

    Node* node_ptr = list->head;
    for (int current_node = 1; current_node < logic_id; current_node++) {
        node_ptr = node_ptr->next;
    }

    elem_t return_value = node_ptr->value;
    return return_value;
}

void ListDestructor(List* list) {

    Node* curr_ptr = list->head;
    Node* next_node_ptr = nullptr;
    while(curr_ptr != nullptr) {
        if (curr_ptr) {
            free((char*)curr_ptr->value);
            curr_ptr->value = nullptr;
        }
        next_node_ptr   = curr_ptr->next;
        free (curr_ptr);
        curr_ptr = next_node_ptr;
    }
}

void _ListDump(List* list, const char* file, const char* func, int line) {
    
    Node* curr_ptr = list->head;
    printf("\n" Blue "******************************" Blinking "List Dump" Blue "******************************" Gray "\n");
    PrintFuncPosition();
    printf("\nsize: %d;\thead: %p;\t tail: %p\n", list->size, list->head, list->tail);
    printf("From Head to Tail:\n");
    for (int i = 1; i <= list->size && curr_ptr != nullptr; i++, curr_ptr = curr_ptr->next) {
        printf("[%d] = %s\n", i, curr_ptr->value);
    }

    curr_ptr = list->tail;
    printf("\n\nFrom Tail to Head:\n");
    for (int i = 1; i <= list->size && curr_ptr != nullptr; i++, curr_ptr = curr_ptr->prev) {
        printf("[%d] = %s\n", i, curr_ptr->value);
    }
    printf("\n");

    // ListGraph(list);
}

int ListGraph(List *list) {

    DotStartGraph("data//list.dot");
    Validator(dot_file == nullptr, "in openning file:'data//list.dot'", return OPEN_FILE_ERROR;);

    const char dot_header[] = "digraph List {\n"
                              "\tdpi = 100;\n"
                              "\tfontname = \"Comic Sans MS\";\n"
                              "\tfontsize = 20;\n"
                              "\trankdir  = LR;\n";
    DotPrint(dot_header);

    DotSetGraph("lightgreen", 1.3, 0.5, "rounded", "green", 2.);
    DotSetEdge("darkgrey", "onormal", 1., 1.2);

    // General list information
    DotPrint("List_Inform [shape = record, color = purple, style = solid, label = \"size:%d | Dump number: %d\"]\n\n",\
             list->size, list->Dump_Number);

    DotPrint("node%d [shape = record, color = red, style = solid, label = \"logic id:%d|<p> prev:%p| value:%s|<n>next:%p\"]\n", //head
            1, 1, list->head->prev, list->head->value, list->head->next);
    DotPrint("node%d [shape = record, color = red, style = solid, label = \"logic id:%d|<p> prev:%p| value:%s|<n>next:%p\"]\n", //tail
            list->size, list->size, list->tail->prev, list->tail->value, list->tail->next);
    DotPrint("node%d [shape = record, color = grey, style = solid, label = \"NULL\"]\n", //left null
            0);
    DotPrint("node%d [shape = record, color = grey, style = solid, label = \"NULL\"]\n", //right null
            list->size + 1);
    //other nodes
    Node* node_ptr = list->head->next;
    for (int phys_node_id = 2; phys_node_id < list->size; phys_node_id++, node_ptr = node_ptr->next) {

        DotPrint("node%d [shape = record, color = green, style = solid, label = \"logic id:%d|<p> prev:%p| value:%s|<n>next:%p\"]\n", 
        phys_node_id, phys_node_id, node_ptr->prev, node_ptr->value, node_ptr->next);
    }
    DotPrint("\n\n\n");

    // making invisible connections
    DotPrint("edge[style=invis, constraint = true]")
    int node_counter = 1;
    for ( ; node_counter < list->size; node_counter++) {
        DotPrint("node%d->", node_counter);
    }
    if (list->size > 1) {
        DotPrint("node%d\n", node_counter);
    }

    DotPrint("\nHead -> node%d\n", 1);
    DotPrint("Tail -> node%d -> node%d\n", list->size, list->size + 1);
    DotPrint("node%d -> node%d\n", 0, 1);
    
    // making visible connections
    DotPrint("edge[style=solid, constraint = false]")
    if (list->size > 0) {
        DotPrint("node%d:p -> node%d;", 1, 0);
        DotPrint("node%d:n ", 1);

        int phys_node_id = 2;
        for ( ; phys_node_id <= list->size; phys_node_id++) {
            DotPrint("-> node%d;", phys_node_id);
            DotPrint("node%d:p ->node%d;", phys_node_id, phys_node_id - 1);
            DotPrint("node%d:n ", phys_node_id);
        }
        DotPrint(" -> node%d\n", phys_node_id);
    }

    DotPrint("Head -> node%d\n",  1);
    DotPrint("Tail -> node%d\n",  list->size);

    DotEndGraph(dot_file);
    DotPrintGraph(file, list->Dump_Number);

    list->Dump_Number++;
    return list->Dump_Number;
}