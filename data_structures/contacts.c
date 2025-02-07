/**
 * https://www.hackerrank.com/challenges/contacts/problem
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
 * Memory is not freed for result or tree.
 */


/*****************************************************************************/

#define MAX_CHILDREN			26
#define CHR_2_IDX(c)			(int)((c) - 'a')

#define OP_ADD					"add"


/*****************************************************************************/

typedef struct node_s {

	int							children_leafs;
	struct node_s				*children[MAX_CHILDREN];

} node_t;


/*****************************************************************************/

//
// Trie implementation
//

static node_t *__node_create(void)
{
	node_t *node;

	node = (node_t *)malloc(sizeof(node_t));
	if (!node)
		return NULL;

	node->children_leafs = 0;
	memset(node->children, 0, sizeof(node->children));

	return node;
}

static int __node_insert(node_t *root, char *s)
{
	int i, idx;

	if (!s)
		return 0;

	for (i = 0; i < strlen(s); i++) {
		idx = CHR_2_IDX(s[i]);

		if (!root->children[idx]) {
			root->children[idx] = __node_create();
			if (!root->children[idx])
				return -1;
		}

		root->children_leafs++;
		root = root->children[idx];
	}

	// current not is a valid leaf
	root->children_leafs = 1;

	return 0;
}

static int __node_find(node_t *root, char *s)
{
	int i, idx;

	for (i = 0; i < strlen(s); i++) {
		idx = CHR_2_IDX(s[i]);

		if (!root->children[idx])
			return 0;

		root = root->children[idx];
	}

	return root->children_leafs;
}


/*****************************************************************************/

int* contacts(int queries_rows, int queries_columns, char*** queries,
			int* result_count)
{
	int i, *res;
	node_t *root;
	char *op, *val;

	/****************************************************************
	 * Create tree root.
	 ***************************************************************/
	root = __node_create();
	if (!root)
		return NULL;

	/****************************************************************
	 * Worst case for return array is the number of queries.
	 ***************************************************************/
	res = (int *)malloc(queries_rows * sizeof(int));
	if (!res) {
		free(root);
		return NULL;
	}

	/****************************************************************
	 * Worst case for return array is the number of queries.
	 ***************************************************************/
	*result_count = 0;
	for (i = 0; i < queries_rows; i++) {
		op = queries[i][0];
		val = queries[i][1];

		// add
		if (strcmp(op, OP_ADD) == 0) {
			assert(!__node_insert(root, val));
			continue;
		}

		// find
		res[(*result_count)++] = __node_find(root, val);
	}

	return res;
}


/*****************************************************************************/


int main()
{
	node_t *root;

	//
	root = __node_create();
	if (!root)
		return -1;

	//
	assert(!__node_insert(root, "hack"));
	assert(!__node_insert(root, "hackerrank"));

	//
	printf("h: %d\n", __node_find(root, "h"));
	printf("hac: %d\n", __node_find(root, "hac"));
	printf("hak: %d\n", __node_find(root, "hak"));

	return 0;
}
