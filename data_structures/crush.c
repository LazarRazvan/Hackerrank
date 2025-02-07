/**
 * https://www.hackerrank.com/challenges/crush/problem
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
 * Sweep line algorithm.
 *
 * Create an event for every each interval, where add X at starting of the
 * interval and subtract X and end of interval + 1.
 */

/*****************************************************************************/

typedef struct event_s {

	int			start;
	int			value;

} event_t;


static int __event_cmp(const void *a, const void *b)
{
	event_t *e1, *e2;

	e1 = (event_t *)a;
	e2 = (event_t *)b;

	// ascending by start
	if (e1->start != e2->start)
		return e1->start - e2->start;

	// ascending by value
	return e1->value - e2->value;
}


/*****************************************************************************/

long arrayManipulation(int n, int queries_rows, int queries_columns,
					int** queries)
{
	long sum, max;
	int i, a, b, k;
	event_t *events;

	/****************************************************************
	 * For each querry, create two events; start and end.
	 ***************************************************************/
	events = (event_t *)malloc(2 * queries_rows * sizeof(event_t));
	if (!events)
		return -1;

	for (i = 0; i < queries_rows; i++) {
		a = queries[i][0];
		b = queries[i][1];
		k = queries[i][2];

		// start inteval
		events[2 * i].start = a;
		events[2 * i].value = k;

		// end interval
		events[2 * i + 1].start = b + 1;
		events[2 * i + 1].value = -k;
	}

	/****************************************************************
	 * Sort queries ascending by start position.
	 ***************************************************************/
	qsort(events, 2 * queries_rows, sizeof(event_t), __event_cmp);

	/****************************************************************
	 * Iterate in events and compute max
	 ***************************************************************/
	sum = 0;
	max = 0;
	for (i = 0; i < 2 * queries_rows; i++) {
		sum += events[i].value;

		if (sum > max)
			max = sum;
	}

	//
	free(events);

	return max;
}


/*****************************************************************************/

int main()
{
	int **arr;

	arr = malloc(4 * sizeof(int*));
	arr[0] = malloc(3 * sizeof(int));
	arr[1] = malloc(3 * sizeof(int));
	arr[2] = malloc(3 * sizeof(int));
	arr[3] = malloc(3 * sizeof(int));

	arr[0][0] = 2;
	arr[0][1] = 6;
	arr[0][2] = 8;
	arr[1][0] = 3;
	arr[1][1] = 5;
	arr[1][2] = 7;
	arr[1][0] = 1;
	arr[1][1] = 8;
	arr[1][2] = 1;
	arr[2][0] = 5;
	arr[2][1] = 9;
	arr[2][2] = 15;

	printf("%ld\n", arrayManipulation(4, 3, 3, arr));

	return 0;
}
