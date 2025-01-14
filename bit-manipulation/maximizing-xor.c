/**
 * https://www.hackerrank.com/challenges/maximizing-xor/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>


/*****************************************************************************/

/**
 * Since l and r are smaller or equal than 10^3, we can loop through all
 * possibilities solving in O(N^2).
 */

/*****************************************************************************/

int maximizingXor(int l, int r)
{
	int sum_xor = 0, crt;

	for (int i = l; i <= r; i++) {
		for (int j = i; j <= r; j++) {
			crt = i ^ j;

			if (crt > sum_xor)
				sum_xor = crt;
		}
	}

	return sum_xor;
}

int main()
{
	return 0;
}
