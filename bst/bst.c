#include "bst.h"

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    p->root = NULL;
    p->nil = NULL;
    return p;
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    free(t);
}

void rbtree_find_insert(rbtree *t, node_t *node)
{
    node_t *n;
    node_t *parent;
    n = t->root;

    while (n != NULL)
    {
        parent = n;
        if (n->key > node->key)
        {
            n = n->left;
        }
        else
        {
            n = n->right;
        }
    }

    return node;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    node_t *node;
    node_t *parent;
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    node = rbtree_find(t, key);
    if (node != NULL)
    {
        node->right = new_node;
        new_node->parent = node;
    }
    else
    {
        node = t->root;
        while (node != NULL)
        {
            new_node->parent = node;
            if (node->key > key)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
    }

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *node;
    node = t->root;
    while (node != NULL)
    {
        if (node->key == key)
        {
            printf("찾았다!! %d\n", node->key);
            return node;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}
