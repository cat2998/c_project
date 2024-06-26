#ifndef _BST_H_
#define _BST_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef enum
{
    RBTREE_RED,
    RBTREE_BLACK
} color_t;

typedef int key_t;

typedef struct node_t
{
    color_t color;
    key_t key;
    struct node_t *parent, *left, *right;
} node_t;

typedef struct
{
    node_t *root;
    node_t *nil; // for sentinel
} bstree;

bstree *new_bstree(void);

node_t *bstree_insert(bstree *bst, const key_t key);
node_t *bstree_find(const bstree *bst, const key_t key);
node_t *bstree_min(const bstree *bst);
node_t *bstree_max(const bstree *bst);

int bstree_erase(bstree *bst, node_t *);
void delete_bstree(bstree *bst);
void postOrderTraverse(node_t *deleteNode); // 새로추가

int bstree_to_array(const bstree *bst, key_t *arr, const size_t n);
size_t inOrderTraverse(node_t *treeNode, key_t *arr, size_t i, size_t n); // 새로추가

#endif
