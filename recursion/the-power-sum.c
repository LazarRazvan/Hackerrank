/**
 * https://www.hackerrank.com/challenges/the-power-sum/problem
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

static int __recursion(int x, int n, int number)
{
	int p;

	/****************************************************************
	 * Stop when X is 0 (combination found).
	 ***************************************************************/
	if (!x)
		return 1;

	/****************************************************************
	 * Stop when sum is exceeded (combination not found).
	 ***************************************************************/
	p = (int)pow(number, n);
	if (x < 0 || p > x)
		return 0;

	/****************************************************************
	 * Continue recursion. Either add current number or not.
	 ***************************************************************/
	return __recursion(x, n, number + 1) + __recursion(x - p, n, number + 1);
}

int powerSum(int X, int N)
{
	return __recursion(X, N, 1);
}

/*****************************************************************************/

int main()
{
	printf("%d\n", powerSum(100, 3));

	return EXIT_SUCCESS;
}
