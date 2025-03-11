/**
 * https://www.hackerrank.com/challenges/components-in-graph/problem
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

#define N		30000

//
#define container_of(ptr, type, member) ({					\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})


/*****************************************************************************/
/**
 * Singly linked list.
 */

typedef struct kslist_node_s {

	struct kslist_node_s *next;

} kslist_head_t, kslist_node_t;

#define __kslist_for_each(head, it)				\
	for (it = (head)->next; it; it = it->next)

#define __kslist_for_each_safe(head, it, aux)	\
	for (it = (head)->next, aux = (it ? it->next : NULL); it; it = aux, aux = (it ? it->next : NULL))

static inline bool __kslist_is_empty(kslist_head_t *head)
{
	return head->next == NULL;
}

static inline void __kslist_init(kslist_head_t *head)
{
	head->next = NULL;
}

static inline void __kslist_insert(kslist_head_t *head, kslist_node_t *node)
{
	//
	for (; head->next; head = head->next);

	//
	head->next = node;
	node->next = NULL;
}


/*****************************************************************************/
/**
 * Graph.
 */

typedef struct graph_node_s {

	int					node_no;
	kslist_node_t		node;

} graph_node_t;

//
static inline graph_node_t *__graph_node_create(int node_no)
{
	graph_node_t *node;

	//
	node = (graph_node_t *)malloc(sizeof(graph_node_t));
	if (!node)
		return NULL;

	//
	node->node_no = node_no;

	return node;
}

static inline kslist_head_t *__graph_create(int size, int **gb)
{
	graph_node_t *node;
	kslist_head_t *graph;

	// graph memory
	graph = (kslist_head_t *)malloc(N * sizeof(kslist_head_t));
	if (!graph)
		goto error;

	// graph init
	for (int i = 0; i < N; i++)
		__kslist_init(&graph[i]);

	// graph links
	for (int i = 0; i < size; i++) {
		node = __graph_node_create(gb[i][1]);
		if (!node)
			goto error;

		__kslist_insert(&graph[gb[i][0]], &node->node);

		node = __graph_node_create(gb[i][0]);
		if (!node)
			goto error;

		__kslist_insert(&graph[gb[i][1]], &node->node);
	}

	return graph;

error:
	return NULL;
}

static inline void __graph_destroy(kslist_head_t *graph)
{
	graph_node_t *node;
	kslist_node_t *it, *aux;

	// graph links
	for (int i = 0; i < N; i++) {
		__kslist_for_each_safe(&graph[i], it, aux) {
			node = container_of(it, graph_node_t, node);
			//
			free(node);
		}
	}

	// graph memory
	free(graph);
}

static inline void __graph_print(kslist_head_t *graph)
{
	kslist_node_t *it;
	graph_node_t *node;

	//
	for (int i = 0; i < N; i++) {
		printf("%d: \n", i);

		//
		__kslist_for_each(&graph[i], it) {
			node = container_of(it, graph_node_t, node);

			printf("%d ", node->node_no);
		}

		printf("\n");
	}
}


/*****************************************************************************/

static void __components_no(int node_no, kslist_head_t *graph, bool *visited,
							int *components_no)
{
	kslist_node_t *it;
	graph_node_t *node;

	// set visited
	visited[node_no] = true;

	// increase count
	(*components_no)++;

	// move to all unvisited nodes
	__kslist_for_each(&graph[node_no], it) {
		node = container_of(it, graph_node_t, node);
		//
		if (visited[node->node_no])
			continue;

		//
		__components_no(node->node_no, graph, visited, components_no);
	}
}


/*****************************************************************************/

int* componentsInGraph(int gb_rows, int gb_columns, int** gb, int* result_count)
{
	//int *result;
	bool *visited;
	int *result = NULL;
	kslist_head_t *graph;
	int min = INT_MAX, max = 0, components_no;

	/****************************************************************
	 * Build graph and visited array.
	 ***************************************************************/
	graph = __graph_create(gb_rows, gb);
	if (!graph)
		goto finish;

	//
	visited = (bool *)malloc(N * sizeof(bool));
	if (!visited)
		goto graph_free;

	memset(visited, 0, N * sizeof(bool));

	/****************************************************************
	 * Compute components.
	 ***************************************************************/
	for (int i = 0; i < N; i++) {
		// skip visited nodes
		if (visited[i])
			continue;

		// compute components
		components_no = 0;
		__components_no(i, graph, visited, &components_no);

		// skip 1 node components
		if (components_no == 1)
			continue;

		// reset min and max
		min = (components_no < min) ? components_no : min;
		max = (components_no > max) ? components_no : max;
	}

	printf("min: %d\n", min);
	printf("max: %d\n", max);

	/****************************************************************
	 * Create result.
	 ***************************************************************/
	result = (int *)malloc(2 * sizeof(int));
	if (!result)
		goto visited_free;

	//
	*result_count = 2;
	result[0] = min;
	result[1] = max;

visited_free:
	free(visited);
graph_free:
	__graph_destroy(graph);
finish:
	return result;
}


/*****************************************************************************/

int main()
{
	int n, res_cnt;
	int **gb, *res;

	//
	scanf("%d", &n);

	//
	gb = (int **)malloc(n * sizeof(int*));
	if (!gb)
		return -1;

	for (int i = 0; i < n; i++) {
		//
		gb[i] = malloc(2 * sizeof(int));
		if (!gb[i])
			return -3;

		//
		scanf("%d %d", &gb[i][0], &gb[i][1]);
	}

	//
	res = componentsInGraph(n, 2, gb, &res_cnt);
	printf("%d %d\n", res[0], res[1]);

	//
	for (int i = 0; i < n; i++)
		free(gb[i]);
	free(gb);

	return 0;
}
