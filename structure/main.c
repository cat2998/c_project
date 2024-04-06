#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
    int num, num2;
    Node *node;
    linked_list *list;

    list = init_list();
    while (1)
    {
        printf("어떤값? (-1 입력시 종료) : ");
        scanf("%d", &num);
        if (num == -1)
            break;
        node = init_node(num);
        insert_node(list, node);
    }
    printf("갯수: %d\n", list_size(list));
    printf("리스트: ");
    print_linked_list(list);
    printf("\n");
    while (1)
    {
        printf("어떤값 찾을래? (-1 입력시 종료) : ");
        scanf("%d", &num);
        if (num == -1)
            break;
        node = search_node(list, num);
        if (node == NULL)
            printf("못찾았음\n");
        else
            printf("찾음 %d\n", node->data);
    }
    while (1)
    {
        printf("어떤값 지울래? (-1 입력시 종료) : ");
        scanf("%d", &num);
        if (num == -1)
            break;
        delete_node(list, num);
        printf("갯수: %d\n", list_size(list));
        printf("리스트: ");
        print_linked_list(list);
        printf("\n");
    }
    while (1)
    {
        printf("어떤값 바꿀래? 바꾸고싶은노드값 바꿀값 입력하셈 (-1 -1 입력시 종료) : ");
        scanf("%d %d", &num, &num2);
        if (num == -1 && num2 == -1)
            break;
        update_node(list, num, num2);
        printf("리스트: ");
        print_linked_list(list);
        printf("\n");
    }
    printf("최종 리스트: ");
    print_linked_list(list);
    printf("\n");
    free_linked_list(list);
}

// valgrind ./main