#include "bst.h"

void postorder_delete(node_t *node);

bstree *new_bstree(void)
{
    bstree *p = (bstree *)calloc(1, sizeof(bstree));
    p->root = NULL;
    p->nil = NULL;
    return p;
}

void delete_bstree(bstree *t)
{
    postorder_delete(t->root);
    free(t);
    return;
}

void init_new_node(node_t *new_node, key_t key)
{
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return;
}

void insert_node(bstree *t, node_t *new_node, key_t key)
{
    node_t *node;

    node = t->root;
    if (node == NULL)
    {
        t->root = new_node;
        new_node->parent = NULL;
        init_new_node(new_node, key);
    }
    else
    {
        while (node != NULL)
        {
            if (node->key > key)
            {
                if (node->left == NULL)
                {
                    node->left = new_node;
                    new_node->parent = node;
                    init_new_node(new_node, key);
                    return;
                }
                node = node->left;
            }
            else
            {
                if (node->right == NULL)
                {
                    node->right = new_node;
                    new_node->parent = node;
                    init_new_node(new_node, key);
                    return;
                }
                node = node->right;
            }
        }
    }

    return;
}

node_t *bstree_insert(bstree *t, const key_t key)
{
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    insert_node(t, new_node, key);
    return new_node;
}

node_t *bstree_find(const bstree *t, const key_t key)
{
    node_t *node;
    node = t->root;

    while (node != NULL)
    {
        if (node->key == key)
            return node;
        else if (node->key > key)
            node = node->left;
        else
            node = node->right;
    }

    return node;
}

node_t *bstree_min_max(node_t *node, int direction)
{
    while (node != NULL)
    {
        if (direction == 1)
        {
            if (node->right == NULL)
                return node;
            node = node->right;
        }
        else
        {
            if (node->left == NULL)
                return node;
            node = node->left;
        }
    }

    return node;
}

node_t *bstree_min(const bstree *t)
{
    return bstree_min_max(t->root, 0);
}

node_t *bstree_max(const bstree *t)
{
    return bstree_min_max(t->root, 1);
}

void erase_zero_node(bstree *t, node_t *node)
{
    if (node->parent != NULL)
    {
        if (node->parent->left == node)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
    }
    else
        t->root = NULL;

    free(node);
    return;
}

void erase_one_node(bstree *t, node_t *node)
{
    node_t *sub_node;

    if (node->left != NULL)
        sub_node = node->left;
    else
        sub_node = node->right;

    if (node->parent != NULL)
    {
        if (node->parent->left == node)
            node->parent->left = sub_node;
        else
            node->parent->right = sub_node;
        sub_node->parent = node->parent;
    }
    else
    {
        t->root = sub_node;
        sub_node->parent = NULL;
    }

    free(node);
    return;
}

void erase_multi_node(bstree *t, node_t *node)
{
    int temp;
    node_t *succession_node;

    succession_node = bstree_min_max(node->right, 0);
    temp = succession_node->key;
    if (succession_node->left == NULL && succession_node->right == NULL)
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
    if (node != NULL)
    {
        if (node->left == NULL && node->right == NULL)
            erase_zero_node(t, node);
        else if (node->left == NULL || node->right == NULL)
            erase_one_node(t, node);
        else
            erase_multi_node(t, node);
    }

    return 0;
}

void postorder_delete(node_t *node)
{
    if (node != NULL)
    {
        if (node->left != NULL)
            postorder_delete(node->left);
        if (node->right != NULL)
            postorder_delete(node->right);
        free(node);
    }
    return;
}

int inorder(node_t *node, key_t *arr, int i, int n)
{
    if (i >= n)
        return 0;
    if (node != NULL)
    {
        if (node->left != NULL)
            i = inorder(node->left, arr, i, n);
        arr[i++] = node->key;
        if (node->right != NULL)
            i = inorder(node->right, arr, i, n);
    }
    return i;
}

int bstree_to_array(const bstree *t, key_t *arr, const size_t n)
{
    inorder(t->root, arr, 0, n);
    return 0;
}