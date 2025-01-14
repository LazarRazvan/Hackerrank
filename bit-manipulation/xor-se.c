/**
 * https://www.hackerrank.com/challenges/xor-se/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>

/*****************************************************************************/

/**
 * By examining the array elements, we observe that the value of the n-th
 * element can be determined based on its modulo 4 result:
 *
 * An = index     , if n % 4 == 0
 * An = 1         , if n % 4 == 1
 * An = index + 1 , if n % 4 == 2
 * An = 0         , if n % 4 == 3
 *
 * Additionally, note that for n % 4 == 0:
 * An XOR An+1 XOR An+2 XOR An+3 = 2
 */


/*****************************************************************************/

// Only works if X is a power of two
#define ROUND_X_UP(n, x)	(((n) + ((x) - 1)) &~ ((x) - 1))

/**
 * Looking at array elements, we can see that based on modulo 4 value, we can
 * determine the value of n-th element.
 */
long get_nth_element(long index)
{
	switch (index % 4) {
	case 0:
		return index;
	case 1:
		return 1;
	case 2:
		return index + 1;
	case 3:
		return 0;
	default:
		break;
   }

	return 0;
}

long xorSequence(long l, long r)
{
	long i, intervals_of_4, left_multiple_of_4, sum;

	/**
	 * Calculate the number of 4-element intervals within the range [l; r],
	 * starting from a number that is a multiple of 4.
	 *
	 * If the number of intervals is even, the resulting sum will be 0.
	 * If the number of intervals is odd, the resulting sum will be 2.
	 */
	left_multiple_of_4 = ROUND_X_UP(l, 4);
	intervals_of_4 = (r - left_multiple_of_4 + 1) / 4;

	//
	sum = (intervals_of_4 % 2) ? 2 : 0;

	/**
	 * If no complete interval exists, iterate through all elements
	 * and calculate the sum. In this case, there will be fewer than 4 elements.
	 */
	if (!intervals_of_4) {
		for (i = l; i <= r; i++)
			sum ^= get_nth_element(i);

		goto finish;
	}

	/**
	 * If there are complete intervals, include the remaining elements
	 * on the left and right to complete the calculation.
	 */
	// left
	for (i = l; i < left_multiple_of_4; i++)
		sum ^= get_nth_element(i);

	// right
	for (i = left_multiple_of_4 + intervals_of_4 * 4; i <= r; i++)
		sum ^= get_nth_element(i);

finish:
	return sum;
}

int main()
{
	return 0;
}
