/**
 * https://www.hackerrank.com/challenges/self-balancing-tree/problem
 * Copyright (C) 2025 Lazar Razvan.
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


/*****************************************************************************/

#define MAX(a, b)		((a > b) ? a : b)


/*****************************************************************************/

/**
 * AVL node
 */
typedef struct node {

	int			val;		// value
	struct node	*left;		// left child
	struct node	*right;		// right child
	int			ht;			// height of the node

} node;

static node *__node_create(int val)
{
	node *n = NULL;

	//
	n = (node *)malloc(sizeof(node));
	if (!n)
		goto finish;

	//
	n->val = val;
	n->ht = 0;
	n->left = NULL;
	n->right = NULL;

finish:
	return n;
}

static int __node_height(node *node)
{
	if (!node)
		return -1;

	return node->ht;
}

static int __node_bf(node *node)
{
	return (__node_height(node->left) - __node_height(node->right));
}


/*****************************************************************************/

/**
 *        y                                x
 *      /  \                             /   \
 *     x    T3 ------------------->     T1    y
 *   /  \                                   /  \
 *  T1  T2                                 T2  T3
 */
static node *__right_rotate(node *y)
{
	node *x, *T2;

	//
	x = y->left;
	T2 = x->right;

	// reset pointers
	x->right = y;
	y->left = T2;

	// reset height
	y->ht = 1 + MAX(__node_height(y->left), __node_height(y->right));
	x->ht = 1 + MAX(__node_height(x->left), __node_height(x->right));

	return x;
}

/**
 *        y                                x
 *      /  \                             /   \
 *     T1   x ------------------->      y    T3
 *         / \                        /  \
 *        T2 T3                      T1  T2
 */
static node *__left_rotate(node *y)
{
	node *x, *T2;

	//
	x = y->right;
	T2 = x->left;

	// reset pointers
	x->left = y;
	y->right = T2;

	// reset height
	y->ht = 1 + MAX(__node_height(y->left), __node_height(y->right));
	x->ht = 1 + MAX(__node_height(x->left), __node_height(x->right));

	return x;
}


/*****************************************************************************/

node *insert(node *root, int new_val)
{
	int balance_factor;

	/****************************************************************
	 * Add new node to AVL tree.
	 ***************************************************************/
	if (!root)
		return __node_create(new_val);

	//
	if (new_val < root->val)
		root->left = insert(root->left, new_val);
	else
		root->right = insert(root->right, new_val);

	/****************************************************************
	 * Reset height.
	 ***************************************************************/
	root->ht = 1 + MAX(__node_height(root->left), __node_height(root->right));

	/****************************************************************
	 * Rebalance the tree.
	 ***************************************************************/
	balance_factor = __node_bf(root);

	// right right
	if (balance_factor < -1 && new_val > root->right->val)
		return __left_rotate(root);

	// right left
	if (balance_factor < -1 && new_val < root->right->val) {
		root->right = __right_rotate(root->right);
		return __left_rotate(root);
	}

	// left right
	if (balance_factor > 1 && new_val > root->left->val) {
		root->left = __left_rotate(root->left);
		return __right_rotate(root);
	}

	// left left
	if (balance_factor > 1 && new_val < root->left->val)
		return __right_rotate(root);

	//
	return root;
}


/*****************************************************************************/

int main()
{
	return 0;
}
