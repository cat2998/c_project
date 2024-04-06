#include "bst.h"

int main(void)
{
    int num;
    rbtree *tree;
    tree = new_rbtree();
    scanf("%d", &num);
    rbtree_insert(tree, num);
    scanf("%d", &num);
    rbtree_insert(tree, num);
    printf_tree(tree);
}