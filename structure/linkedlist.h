#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Node;

typedef struct linked_list
{
    Node *head;
    Node *tail;
} linked_list;

linked_list *init_list();
Node *init_node(int data);
void insert_node(linked_list *list, Node *node);
void print_linked_list(linked_list *list);
int is_empty_list(linked_list *list);
void free_linked_list(linked_list *list);
int list_size(linked_list *list);
Node *search_node(linked_list *list, int data);
void delete_node(linked_list *list, int data);
void update_node(linked_list *list, int old, int new);

#endif