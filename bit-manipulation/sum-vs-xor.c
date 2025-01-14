/**
 * https://www.hackerrank.com/challenges/sum-vs-xor/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************/

/**
 * We can consider that XOR is a sum without carry, while sum is with carry.
 *
 * The total number of possibilities for which n + x = n XOR x is equal to
 * 2 raised to the power of the total number of unset bits in n. This is
 * because, for each unset bit, we can choose either 0 or 1 without generating
 * a carry bit.
 */

/*****************************************************************************/

long get_unset_bits_no(long n)
{
	int i, unset_bits_no = 0;
	bool heighest_bit = false;

	for (i = sizeof(long) * 8 - 1; i >= 0; i--) {
		// get heighest bit
		if ((1UL << i) & n) {
			heighest_bit = true;
			continue;
		}

		// only count unset bits after heighest bit set
		if (heighest_bit)
			unset_bits_no++;
	}

	return unset_bits_no;
}

long sumXor(long n)
{
	return (1UL << get_unset_bits_no(n));
}

int main()
{
	return 0;
}
