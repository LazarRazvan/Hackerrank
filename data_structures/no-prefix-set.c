/**
 * https://www.hackerrank.com/challenges/no-prefix-set/problem
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
 * Memory is not freed for tree.
 */


/*****************************************************************************/

// a - j (inclusive)
#define MAX_CHILDREN			10
#define CHR_2_IDX(c)			(int)((c) - 'a')


/*****************************************************************************/

typedef struct node_s {

	bool						leaf;
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

	node->leaf = false;
	memset(node->children, 0, sizeof(node->children));

	return node;
}

static int __node_insert(node_t *root, char *s)
{
	int i, idx;

	if (!s)
		return 0;

	for (i = 0; i < strlen(s) - 1; i++) {
		idx = CHR_2_IDX(s[i]);

		// a leaf in path represent a common prefix
		if (root->children[idx]) {
			if (root->children[idx]->leaf)
				return 1;
		} else {
			root->children[idx] = __node_create();
			if (!root->children[idx])
				return 1;
		}

		root = root->children[idx];
	}

	// existing leaf node represent a common prefix
	idx = CHR_2_IDX(s[i]);
	if (root->children[idx]) {
		return 1;
	} else {
		root->children[idx] = __node_create();
		if (!root->children[idx])
			return 1;

		root->children[idx]->leaf = true;
	}

	return 0;
}


/*****************************************************************************/

void noPrefix(int words_count, char** words)
{
	int i;
	node_t *root;

	/****************************************************************
	 * Create tree root.
	 ***************************************************************/
	root = __node_create();
	if (!root)
		goto error;

	/****************************************************************
	 * Insert words and check for insert errors.
	 ***************************************************************/
	for (i = 0; i < words_count; i++) {
		if (__node_insert(root, words[i]))
			goto error;
	}

//success:
	printf("GOOD SET\n");
	return;

error:
	printf("BAD SET\n%s\n", words[i]);
}


/*****************************************************************************/


int main()
{
	return 0;
}
