/**
 * https://www.hackerrank.com/challenges/counter-game/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <math.h>
#include <stdio.h>
#include <stdint.h>


/*****************************************************************************/

/**
 * When the number is a power of two, dividing it by 2 repeatedly shifts the
 * single set bit to the right until it reaches position 0. However, if the
 * number is not a power of two, subtracting the next lower power of two
 * effectively removes the most significant set bit.
 *
 * The solution involves counting the total number of set bits and the leading
 * zeroes in the number. If the total count of set bits is odd, Richard will
 * always win. Otherwise, Louise will win.
 */

/*****************************************************************************/

char* counterGame(long n)
{
	uint8_t trailing_zeroes = 0, total_bits_set = 0;

	// corner case
	if (n == 1)
		return "Richard";

	// count trailing zeroes and total bits set
	for (int i = 0; i < 63; i++) {
		// total bits set
		if ((1UL << i) & n) {
			total_bits_set++;
			continue;
		}

		// trailing zeroes
		if (!total_bits_set)
			trailing_zeroes++;
	}

	if ((trailing_zeroes + total_bits_set) % 2)
		return "Richard";
	else
		return "Louise";
}

int main()
{
	return 0;
}
