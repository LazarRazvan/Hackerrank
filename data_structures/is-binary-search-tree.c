/**
 * https://www.hackerrank.com/challenges/is-binary-search-tree/problem
 * Copyright (C) 2025 Lazar Razvan.
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


/*****************************************************************************/

/**
 * All nodes in the left subtree must be less than root and all nodes in the
 * right subtree must be greater than root.
 */

/*****************************************************************************/

typedef struct node_s {

	struct node_s		*left;
	struct node_s		*right;
	int					data;

} node_t;

/*****************************************************************************/

static bool __check_bst_utils(node_t *node, int min, int max)
{
	//
	if (!node)
		return true;

	//
	if (node->data <= min || node->data >= max)
		return false;

	return __check_bst_utils(node->left, min, node->data) &&
			__check_bst_utils(node->right, node->data, max);
}

bool checkBST(node_t *root)
{
	return __check_bst_utils(root, INT_MIN, INT_MAX);
}


/*****************************************************************************/

int main()
{
	return 0;
}
