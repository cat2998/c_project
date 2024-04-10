#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
	rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
	t->nil = (node_t *)calloc(1, sizeof(node_t));
	t->nil->color = RBTREE_BLACK;
	t->root = t->nil;
	return t;
}

void postorder_delete(rbtree *t, node_t *node)
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

void delete_rbtree(rbtree *t)
{
	postorder_delete(t, t->root);
	free(t->nil);
	free(t);
	return;
}

void rbtree_insert_node(rbtree *t, node_t *node)
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

void left_rotate(rbtree *t, node_t *x)
{
	node_t *y;

	y = x->right;
	x->right = y->left;
	if (y->left != t->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == t->nil)
		t->root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return;
}

void right_rotate(rbtree *t, node_t *x)
{
	node_t *y;

	y = x->left;
	x->left = y->right;
	if (y->right != t->nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == t->nil)
		t->root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
	return;
}

void rbtree_insert_fixup(rbtree *t, node_t *node)
{
	node_t *uncle;

	if (node->parent != t->nil && node->parent->color == RBTREE_RED) // 부모가 red
	{
		if (node->parent == node->parent->parent->left) // 부모가 할아버지의 왼쪽자식
		{
			uncle = node->parent->parent->right;
			if (uncle->color == RBTREE_BLACK) // 삼촌이 black
			{
				if (node->parent->right == node) // 본인이 부모의 오른쪽자식
				{								 // (case 3) 부모가 red, 삼촌이 black, 부모가 할아버지의 왼쪽이고 본인은 부모의 오른쪽이면 => 부모기준 왼쪽 회전 후 case2 실행
					left_rotate(t, node->parent);
					node = node->left;
				}
				node->parent->color = RBTREE_BLACK;		  // 본인이 부모의 왼쪽자식
				node->parent->parent->color = RBTREE_RED; // (case 2) 부모가 red, 삼촌이 black, 오른쪽 일직선이면 => 할아버지와 부모 색 바꾸고 할아버지기준 오른쪽 회전
				right_rotate(t, node->parent->parent);
			}
			else if (uncle->color == RBTREE_RED) // 삼촌이 red
			{									 // (case 1) 부모가 red, 삼촌이 red 이면 => 부모와 삼촌 black으로, 할아버지 red로 바꾸고 할아버지 다시 검사
				node->parent->color = RBTREE_BLACK;
				uncle->color = RBTREE_BLACK;
				node->parent->parent->color = RBTREE_RED;
				rbtree_insert_fixup(t, node->parent->parent);
			}
		}
		else // 부모가 할아버지의 오른쪽자식
		{
			uncle = node->parent->parent->left;
			if (uncle->color == RBTREE_BLACK) // 삼촌이 black
			{
				if (node->parent->left == node) // 본인이 부모의 왼쪽자식
				{								// (case 3`) 부모가 red, 삼촌이 black, 부모가 할아버지의 오른쪽이고 본인은 부모의 왼쪽이면 => 부모기준 오른쪽 회전 후 case2 실행
					right_rotate(t, node->parent);
					node = node->right;
				}
				node->parent->color = RBTREE_BLACK;		  // 본인이 부모의 오른쪽자식
				node->parent->parent->color = RBTREE_RED; // (case 2`) 부모가 red, 삼촌이 black, 왼쪽 일직선이면 => 할아버지와 부모 색 바꾸고 할아버지기준 왼쪽 회전
				left_rotate(t, node->parent->parent);
			}
			else if (uncle->color == RBTREE_RED) // 삼촌이 red
			{									 // (case 1) 부모가 red, 삼촌이 red 이면 => 부모와 삼촌 black으로, 할아버지 red로 바꾸고 할아버지 다시 검사
				node->parent->color = RBTREE_BLACK;
				uncle->color = RBTREE_BLACK;
				node->parent->parent->color = RBTREE_RED;
				rbtree_insert_fixup(t, node->parent->parent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;

	return;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
	node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

	new_node->key = key;
	rbtree_insert_node(t, new_node);
	rbtree_insert_fixup(t, new_node);

	return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
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

node_t *rbtree_min_max(const rbtree *t, node_t *node, int direction)
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

node_t *rbtree_min(const rbtree *t)
{
	return rbtree_min_max(t, t->root, 0);
}

node_t *rbtree_max(const rbtree *t)
{
	return rbtree_min_max(t, t->root, 1);
}

node_t *erase_zero_node(rbtree *t, node_t *node)
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
	t->nil->parent = node->parent;

	free(node);
	return t->nil;
}

node_t *erase_one_node(rbtree *t, node_t *node)
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
	return sub_node;
}

node_t *erase_multi_node(rbtree *t, node_t *node, int *delete_color)
{
	int temp;
	node_t *successor;
	node_t *doubly_node;

	successor = rbtree_min_max(t, node->right, 0);
	temp = successor->key;
	*delete_color = successor->color;
	if (successor->left == t->nil && successor->right == t->nil)
		doubly_node = erase_zero_node(t, successor);
	else
		doubly_node = erase_one_node(t, successor);
	node->key = temp;

	return doubly_node;
}

void rbtree_delete_fixup(rbtree *t, node_t *node)
{
	node_t *sibling;

	if (node->parent != t->nil && node->color == RBTREE_BLACK)
	{
		if (node == node->parent->left) // doubly_black이 부모의 왼쪽 자녀일때
		{
			sibling = node->parent->right;
			if (sibling->color == RBTREE_RED) // 형제가 red
			{								  // (case 1) 부모와 형제의 색을 바꿔주고, 부모를 기준으로 왼쪽 회전. 그러면 형제가 black 되고, case 2, 3, 4 확인
				sibling->color = node->parent->color;
				node->parent->color = RBTREE_RED;
				left_rotate(t, node->parent);
				sibling = node->parent->right;
			}
			if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK) // 형제의 모든 자녀가 black이면
			{
				sibling->color = RBTREE_RED;		   // (case 2) doubly_black과 형제의 black을 모아서 부모에서 전달하면 형제는 red가 된다.
				if (node->parent->color == RBTREE_RED) // 부모가 원래 red였다면 black으로 바꾸고 종료, doubly-black이 되었다면 부모의 위치에서 다시 재귀
				{
					node->parent->color = RBTREE_BLACK;
					return;
				}
				else
					rbtree_delete_fixup(t, node->parent);
			}
			else // 형제가 black
			{
				if (sibling->left->color == RBTREE_RED) // 형제의 왼쪽 자녀가 red
				{										// (case 3) 형제는 red, 왼쪽 자녀는 black으로 바꾸고 형제를 기준으로 오른쪽 회전. 그리고 case 4 적용
					sibling->color = RBTREE_RED;
					sibling->left->color = RBTREE_BLACK;
					right_rotate(t, sibling);
					sibling = node->parent->right;
				}
				// 형제의 오른쪽 자녀가 red
				// (case 4) 형제는 부모의 색으로, 부모와 오른쪽 자녀는 black으로 바꾸고 부모를 기준으로 왼쪽회전
				sibling->color = node->parent->color;
				node->parent->color = RBTREE_BLACK;
				sibling->right->color = RBTREE_BLACK;
				left_rotate(t, node->parent);
			}
		}
		else // doubly_black이 부모의 오른쪽 자녀일때
		{
			sibling = node->parent->left;
			if (sibling->color == RBTREE_RED) // 형제가 red
			{								  // (case 1) 부모와 형제의 색을 바꿔주고, 부모를 기준으로 오른쪽 회전. 그러면 형제가 black 되고, case 2, 3, 4 확인
				sibling->color = node->parent->color;
				node->parent->color = RBTREE_RED;
				right_rotate(t, node->parent);
				sibling = node->parent->left;
			}
			if (sibling->left->color == RBTREE_BLACK && sibling->right->color == RBTREE_BLACK) // 형제의 모든 자녀가 black이면
			{
				sibling->color = RBTREE_RED;		   // (case 2) doubly_black과 형제의 black을 모아서 부모에서 전달하면 형제는 red가 된다.
				if (node->parent->color == RBTREE_RED) // 부모가 원래 red였다면 black으로 바꾸고 종료, doubly-black이 되었다면 부모의 위치에서 다시 재귀
				{
					node->parent->color = RBTREE_BLACK;
					return;
				}
				else
					rbtree_delete_fixup(t, node->parent);
			}
			else // 형제가 black
			{
				if (sibling->right->color == RBTREE_RED) // 형제의 오른쪽 자녀가 red
				{										 // (case 3) 형제는 red, 오른쪽 자녀는 black으로 바꾸고 형제를 기준으로 왼쪽 회전. 그리고 case 4 적용
					sibling->color = RBTREE_RED;
					sibling->right->color = RBTREE_BLACK;
					left_rotate(t, sibling);
					sibling = node->parent->left;
				}
				// 형제의 왼쪽 자녀가 red
				// (case 4) 형제는 부모의 색으로, 부모와 왼쪽 자녀는 black으로 바꾸고 부모를 기준으로 오른쪽회전
				sibling->color = node->parent->color;
				node->parent->color = RBTREE_BLACK;
				sibling->left->color = RBTREE_BLACK;
				right_rotate(t, node->parent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p)
{
	int delete_color;
	node_t *node;
	node_t *doubly_node = NULL;

	node = rbtree_find(t, p->key);
	if (node != t->nil)
	{
		delete_color = node->color;
		if (node->left == t->nil && node->right == t->nil)
			doubly_node = erase_zero_node(t, node);
		else if (node->left == t->nil || node->right == t->nil)
			doubly_node = erase_one_node(t, node);
		else
			doubly_node = erase_multi_node(t, node, &delete_color);
	}

	if (delete_color == RBTREE_BLACK)
	{
		if (doubly_node != t->nil && doubly_node->color == RBTREE_RED)
			doubly_node->color = RBTREE_BLACK;
		else
			rbtree_delete_fixup(t, doubly_node);
	}

	return 0;
}

int inorder(const rbtree *t, node_t *node, key_t *arr, int i, int n)
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

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
	inorder(t, t->root, arr, 0, n);
	return 0;
}