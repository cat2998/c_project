#include "bst.h"

#include <stdlib.h>

bstree *new_bstree(void)
{
    bstree *t = (bstree *)calloc(1, sizeof(bstree));
    t->nil = (node_t *)calloc(1, sizeof(node_t));
    t->nil->color = RBTREE_BLACK;
    t->root = t->nil;
    return t;
}

void postorder_delete(bstree *t, node_t *node)
{
    if (node != t->nil)
    {
        if (node->left != t->nil)
            postorder_delete(t, node->left);
        if (node->right != t->nil)
            postorder_delete(t, node->right);
        free(node);
    }
    return;
}

void delete_bstree(bstree *t)
{
    postorder_delete(t, t->root);
    free(t->nil);
    free(t);
    return;
}

void rbtree_insert_node(bstree *t, node_t *node)
{
    node_t *parent;
    node_t *compare;

    parent = t->nil;
    compare = t->root;
    while (compare != t->nil)
    {
        parent = compare;
        if (compare->key < node->key)
            compare = compare->right;
        else
            compare = compare->left;
    }

    if (parent == t->nil)
        t->root = node;
    else if (parent->key < node->key)
        parent->right = node;
    else
        parent->left = node;
    node->parent = parent;

    node->color = RBTREE_RED;
    node->left = t->nil;
    node->right = t->nil;
    return;
}

node_t *bstree_insert(bstree *t, const key_t key)
{
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    new_node->key = key;
    rbtree_insert_node(t, new_node);

    return new_node;
}

node_t *bstree_find(const bstree *t, const key_t key)
{
    node_t *node;
    node = t->root;

    while (node != t->nil)
    {
        if (node->key == key)
            return node;
        else if (node->key > key)
            node = node->left;
        else
            node = node->right;
    }
    if (node == t->nil)
        node = NULL;

    return node;
}

node_t *bstree_min_max(const bstree *t, node_t *node, int direction)
{
    while (node != t->nil)
    {
        if (direction)
        {
            if (node->right == t->nil)
                return node;
            node = node->right;
        }
        else
        {
            if (node->left == t->nil)
                return node;
            node = node->left;
        }
    }

    return node;
}

node_t *bstree_min(const bstree *t)
{
    return bstree_min_max(t, t->root, 0);
}

node_t *bstree_max(const bstree *t)
{
    return bstree_min_max(t, t->root, 1);
}

void erase_zero_node(bstree *t, node_t *node)
{
    if (node->parent == t->nil)
        t->root = t->nil;
    else
    {
        if (node->parent->left == node)
            node->parent->left = t->nil;
        else
            node->parent->right = t->nil;
    }

    free(node);
    return;
}

void erase_one_node(bstree *t, node_t *node)
{
    node_t *sub_node;

    if (node->left != t->nil)
        sub_node = node->left;
    else
        sub_node = node->right;

    if (node->parent == t->nil)
    {
        t->root = sub_node;
        sub_node->parent = t->nil;
    }
    else
    {
        if (node->parent->left == node)
            node->parent->left = sub_node;
        else
            node->parent->right = sub_node;
        sub_node->parent = node->parent;
    }

    free(node);
    return;
}

void erase_multi_node(bstree *t, node_t *node)
{
    int temp;
    node_t *succession_node;

    succession_node = bstree_min_max(t, node->right, 0);
    temp = succession_node->key;
    if (succession_node->left == t->nil && succession_node->right == t->nil)
        erase_zero_node(t, succession_node);
    else
        erase_one_node(t, succession_node);
    node->key = temp;

    return;
}

int bstree_erase(bstree *t, node_t *p)
{
    node_t *node;

    node = bstree_find(t, p->key);
    if (node != t->nil)
    {
        if (node->left == t->nil && node->right == t->nil)
            erase_zero_node(t, node);
        else if (node->left == t->nil || node->right == t->nil)
            erase_one_node(t, node);
        else
            erase_multi_node(t, node);
    }

    return 0;
}

int inorder(const bstree *t, node_t *node, key_t *arr, int i, int n)
{
    if (i >= n)
        return 0;
    if (node != t->nil)
    {
        if (node->left != t->nil)
            i = inorder(t, node->left, arr, i, n);
        arr[i++] = node->key;
        if (node->right != t->nil)
            i = inorder(t, node->right, arr, i, n);
    }
    return i;
}

int bstree_to_array(const bstree *t, key_t *arr, const size_t n)
{
    inorder(t, t->root, arr, 0, n);
    return 0;
}
