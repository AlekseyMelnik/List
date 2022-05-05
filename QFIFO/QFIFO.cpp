#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


struct complex_number {  //�������� ��������� ����������� �����
    int real;
    int imagine;
};

struct Node
{
    complex_number data;
    Node* next;
};

struct List
{
    int size;
    Node* head;
    Node* end;
};

List* createList(complex_number data);
Node* listAddEnd(List* list, complex_number data);
Node* listAddStart(List* list, complex_number data);
Node* listAddAfter(List* list, complex_number data, complex_number num_after);
Node* deleteListHead(List* list);
Node* deleteListEnd(List* list);
Node* deleteListData(List* list, complex_number data);
List* deleteList(List* list);
Node* findNode(List* list, complex_number data);
void printList(List* list);
int listLength(List* list);
bool checkListExist(List* list);
List* reverseList(List* list);

int main()
{
    List* list = NULL;
    complex_number num;
    num.imagine = 2;
    num.real = 1;
    list = createList(num);




    listAddEnd(list, num);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    listAddEnd(list, num);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    list->head = listAddStart(list, num);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    listAddAfter(list, num, num);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    reverseList(list);
    printf("Reversed List:\n");
    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    list->head = deleteListHead(list);
    deleteListEnd(list);
    list->head = deleteListData(list, num);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    printf("Find node with data 3: %p, Find node with data -100: %p\n", findNode(list, num), findNode(list, num));
    puts("");

    list = deleteList(list);

    printList(list);
    if (list != NULL)
    {
        printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list)); // error beacause of unexisting of List
    }
    return 0;
}

List* createList(complex_number data)
{
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->next = NULL;
    new_node->data = data;

    new_list->head = new_node;
    new_list->end = new_node;
    new_list->size = 1;

    return new_list;
}

Node* listAddEnd(List* list, complex_number data)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    Node* temp_ptr = list->end;

    new_node->data = data;
    new_node->next = NULL;
    temp_ptr->next = new_node;

    list->size++;
    list->end = new_node;

    return new_node;
}

Node* listAddStart(List* list, complex_number data)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;

    list->size++;

    return list->head;
}

Node* listAddAfter(List* list, complex_number data, complex_number num_after)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;

    Node* temp_ptr = list->head;
    Node* previous_tmp_node = temp_ptr;

    int check = 0;
    int check_end = 0;
    if (list->end->data.real == num_after.real)
    {
        check_end = 1;
    }

    do
    {
        if (temp_ptr->data.real == num_after.real)
        {
            check = 1;
        }

        previous_tmp_node = temp_ptr;
        temp_ptr = temp_ptr->next;

        if (!temp_ptr)
        {
            break;
        }
    } while (previous_tmp_node->data.real != num_after.real && temp_ptr);

    if (check == 1)
    {
        previous_tmp_node->next = new_node;
        new_node->next = temp_ptr;

        list->size++;
        if (check_end == 1)
        {
            list->end = new_node;
        }
    }

    return new_node;
}

Node* deleteListHead(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }

    Node* temp_head = list->head->next;

    free(list->head);

    list->size--;

    return temp_head;
}

Node* deleteListEnd(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }

    Node* temp_ptr = list->head;
    Node* previous_tmp_node = temp_ptr;

    do
    {
        previous_tmp_node = temp_ptr;
        temp_ptr = temp_ptr->next;

        if (!temp_ptr)
        {
            break;
        }
    } while (temp_ptr->next != NULL);

    previous_tmp_node->next = NULL;
    free(temp_ptr);

    list->size--;
    list->end = previous_tmp_node;

    return list->head;
}

Node* deleteListData(List* list, complex_number data)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }
    else if (findNode(list, data) == NULL)
    {
        return NULL;
    }

    Node* temp_node = list->head;
    Node* previous_tmp_node = temp_node;

    if (data.real == list->head->data.real)
    {
        list->head = deleteListHead(list);
    }
    else if (data.real == list->end->data.real)
    {
        deleteListEnd(list);
    }
    else
    {
        while (temp_node->data.real != data.real)
        {
            previous_tmp_node = temp_node;
            temp_node = temp_node->next;
        }
        previous_tmp_node->next = temp_node->next;
        free(temp_node);
        list->size--;
    }

    return list->head;
}

List* deleteList(List* list)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    while (list->size != 0)
    {
        list->head = deleteListEnd(list);
    }

    free(list);

    return NULL;
}

Node* findNode(List* list, complex_number data)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* temp_ptr = list->head;

    while (temp_ptr != NULL)
    {
        if (temp_ptr->data.real == data.real)
        {
            return temp_ptr;
        }
        temp_ptr = temp_ptr->next;
    }

    return NULL;
}

void printList(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return;
    }

    Node* printed = list->head;

    while (printed != NULL)
    {
        printf("Real: %d  Imagine:%d ;\n", printed->data.real,printed->data.imagine);
        printed = printed->next;
    }
}

int listLength(List* list)
{
    if (checkListExist(list))
    {
        return -1;
    }

    Node* temp_ptr = list->head;
    int count = 0;

    while (temp_ptr != NULL)
    {
        temp_ptr = temp_ptr->next;
        count++;
    }

    return count;
}

bool checkListExist(List* list)
{
    if (list == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

List* reverseList(List* list)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* previous_node = NULL;
    Node* current_node = list->head;
    Node* next_node = NULL;
    Node* new_tail_node = list->head;

    while (current_node != NULL)
    {
        next_node = current_node->next;
        current_node->next = previous_node;
        previous_node = current_node;
        current_node = next_node;
    }

    list->head = previous_node;
    list->end = new_tail_node;

    return list;
}