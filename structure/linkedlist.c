#include "linkedlist.h"

linked_list *init_list()
{
    linked_list *list = malloc(sizeof(linked_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *init_node(int data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insert_node(linked_list *list, Node *node)
{
    if (is_empty_list(list))
        list->head = node;
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
    }
    list->tail = node;
    return;
}

void print_linked_list(linked_list *list)
{
    Node *node = list->head;
    if (is_empty_list(list))
    {
        printf("비었음");
        return;
    }
    while (1)
    {
        printf("%d ", node->data);
        if (node->next == NULL)
            break;
        node = node->next;
    }
    return;
}

int is_empty_list(linked_list *list)
{
    if (list->head == NULL)
        return 1;
    else
        return 0;
}

int list_size(linked_list *list)
{
    int cnt = 0;
    Node *node = list->head;

    while (node != NULL)
    {
        cnt++;
        node = node->next;
    }
    return cnt;
}

Node *search_node(linked_list *list, int data)
{
    Node *node = list->head;

    while (node != NULL)
    {
        if (node->data == data)
            break;
        node = node->next;
    }
    return node;
}

void free_linked_list(linked_list *list)
{
    Node *node = NULL;
    while (is_empty_list(list) == 0)
    {
        node = list->head;
        list->head = node->next;
        free(node);
    }
    free(list);
    return;
}

void update_node(linked_list *list, int old, int new)
{
    Node *node = NULL;

    node = search_node(list, old);
    if (node == NULL)
        printf("없음");
    else
        node->data = new;
    return;
}

void delete_node(linked_list *list, int data)
{
    Node *delete_node = NULL;

    if (is_empty_list(list))
        return;
    else
    {
        delete_node = search_node(list, data);
        if (delete_node == NULL)
            printf("지울게 없음\n");
        else
        {
            if (list->head == delete_node && list->tail != delete_node)
            {
                list->head = delete_node->next;
                delete_node->next->prev = NULL;
            }
            else if (list->tail == delete_node && list->head != delete_node)
            {
                list->tail = delete_node->prev;
                delete_node->prev->next = NULL;
            }
            else if (list->head == list->tail)
            {
                list->head = NULL;
                list->tail = NULL;
            }
            else
            {
                delete_node->prev->next = delete_node->next;
                delete_node->next->prev = delete_node->prev;
            }
        }
        free(delete_node);
    }
    return;
}