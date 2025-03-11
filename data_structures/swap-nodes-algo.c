/**
 * https://www.hackerrank.com/challenges/swap-nodes-algo/problem
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

/**
 * Binary Tree data structure.
 */
typedef struct node_s {

	int					data;
	struct node_s		*left;
	struct node_s		*right;

} node_t;


static node_t *__node_create(int data)
{
	node_t *node = NULL;

	//
	node = (node_t *)malloc(sizeof(node_t));
	if (!node)
		goto finish;

	//
	node->data = data;
	node->left = NULL;
	node->right = NULL;

finish:
	return node;
}


/*****************************************************************************/
/**
 * Global nodes.
 */
node_t **nodes = NULL;


/*****************************************************************************/

static node_t *__tree_create(int n, int **indexes)
{
	int i;

	/****************************************************************
	 * Create tree nodes.
	 ***************************************************************/
	nodes = (node_t **)malloc(n * sizeof(node_t*));
	if (!nodes)
		goto error;

	//
	for (i = 0; i < n; i++) {
		nodes[i] = __node_create(i + 1);
		if (!nodes[i])
			goto nodes_free;
	}

	/****************************************************************
	 * Link tree nodes.
	 ***************************************************************/
	for (i = 0; i < n; i++) {
		// left
		if (indexes[i][0] != -1)
			nodes[i]->left = nodes[indexes[i][0] - 1];

		// right
		if (indexes[i][1] != -1)
			nodes[i]->right = nodes[indexes[i][1] - 1];
	}

	//
	return nodes[0];

nodes_free:
	while (--i > 0)
		free(nodes[i]);

	free(nodes);

error:
	return NULL;
}

static void __tree_nodes_swap(node_t *root, int h, int k)
{
	node_t *tmp;

	if (!root)
		return;

	if (h % k == 0) {
		tmp = root->left;
		root->left = root->right;
		root->right = tmp;
	}

	__tree_nodes_swap(root->left, h + 1, k);
	__tree_nodes_swap(root->right, h + 1, k);
}

static void __tree_in_order_traversal(node_t *root, int *v, int *cnt)
{
	if (!root)
		return;

	__tree_in_order_traversal(root->left, v, cnt);
	v[(*cnt)++] = root->data;
	__tree_in_order_traversal(root->right, v, cnt);
}

static void __tree_destroy(int n)
{
	//
	for (int i = 0; i < n; i++)
		free(nodes[i]);

	//
	free(nodes);
}


/*****************************************************************************/

int** swapNodes(int indexes_rows, int indexes_columns, int** indexes,
				int queries_count, int* queries, int* result_rows,
				int* result_columns)
{
	int i, idx;
	int **result = NULL;
	node_t *root = NULL;

	/****************************************************************
	 * Create tree data structure.
	 ***************************************************************/
	root = __tree_create(indexes_rows, indexes);
	if (!root)
		goto error;

	/****************************************************************
	 * Alloc result.
	 ***************************************************************/
	*result_rows = queries_count;
	*result_columns = indexes_rows;

	//
	result = (int **)malloc(*result_rows * sizeof(int *));
	if (!result)
		goto tree_free;

	//
	for (i = 0; i < *result_rows; i++) {
		result[i] = (int *)malloc(*result_columns * sizeof(int));
		if (!result[i])
			goto result_free;
	}

	/****************************************************************
	 * Execute queries.
	 ***************************************************************/
	for (int i = 0; i < queries_count; i++) {
		idx = 0;
		__tree_nodes_swap(root, 1, queries[i]);
		__tree_in_order_traversal(root, result[i], &idx);
	}

//success:
	__tree_destroy(indexes_rows);

	return result;

result_free:
	while (--i)
		free(result[i]);

	free(result);
tree_free:
	__tree_destroy(indexes_rows);
error:
	return NULL;
}


/*****************************************************************************/

int main()
{
	int n, t, i, q, res_rows, res_cols;
	int **indexes, **res, *queries;

	/****************************************************************
	 * Read indexes.
	 ***************************************************************/
	scanf("%d", &n);

	//
	indexes = (int **)malloc(n * sizeof(int*));
	if (!indexes)
		goto finish;

	for (i = 0; i < n; i++) {
		//
		indexes[i] = malloc(2 * sizeof(int));
		if (!indexes[i])
			goto indexes_free;

		//
		scanf("%d %d", &indexes[i][0], &indexes[i][1]);
	}

	/****************************************************************
	 * Read queries.
	 ***************************************************************/
	scanf("%d", &t);

	//
	queries = (int *)malloc(t * sizeof(int));
	if (!queries)
		goto indexes_free;

	for (q = 0; q < t; q++)
		scanf("%d", &queries[q]);

	/****************************************************************
	 * Execute.
	 ***************************************************************/
	res = swapNodes(n, 2, indexes, t, queries, &res_rows, &res_cols);
	if (!res)
		goto queries_free;

	//
	for (int l = 0; l < res_rows; l++) {
		for (int m = 0; m < res_cols; m++) {
			printf("%d ", res[l][m]);
		}
		printf("\n");
	}

//result_free:
	for (int l = 0; l < res_rows; l++)
		free(res[l]);

	free(res);

queries_free:
	free(queries);

indexes_free:
	while (--i >= 0)
		free(indexes[i]);

	free(indexes);

finish:
	return 0;
}
