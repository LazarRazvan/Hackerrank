/**
 * https://www.hackerrank.com/challenges/the-great-xor/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************/

/**
 * The total number of possibilities for which n XOR x > x is determined by
 * the number of unset bits in n. For each unset bit, setting it to 1 ensures
 * that the result will always be greater than x, regardless of the values of
 * the subsequent bits.
 *
 * Therefore, the total number of possibilities is given by all combinations
 * that can be created by turning each unset bit to 1.
 */

/*****************************************************************************/

long theGreatXor(long x)
{
	int i;
	long possibilities = 0;
	bool heighest_bit = false;

	for (i = sizeof(long) * 8 - 1; i >= 0; i--) {
		// get heighest bit
		if ((1UL << i) & x) {
			heighest_bit = true;
			continue;
		}

		// only count unset bits after heighest bit set
		if (heighest_bit)
			possibilities += (1UL << i);
	}

	return possibilities;
}

int main()
{
	return 0;
}
