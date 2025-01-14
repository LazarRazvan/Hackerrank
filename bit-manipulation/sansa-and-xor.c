/**
 * https://www.hackerrank.com/challenges/sansa-and-xor/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <math.h>
#include <stdio.h>
#include <stdint.h>


/*****************************************************************************/

/**
 * The first XOR property to consider is associativity, which states:
 * a XOR (b XOR c) = (a XOR b) XOR c = a XOR b XOR c.
 *
 * Using this property, instead of computing the XOR operation for each
 * subarray individually, we can reduce the problem to computing the XOR
 * operation only between the elements of the array.
 *
 * The second XOR property to consider is:
 * - a XOR a XOR a ... XOR a = a, if and only if the number of terms is odd.
 * - a XOR a XOR a ... XOR a = 0, if and only if the number of terms is even.
 *
 * To solve the problem, we need to calculate the occurrences of each array
 * element in all subarrays. For each element, if the number of occurrences
 * is odd, include it in the result by XOR-ing it with the cumulative sum.
 */

/*****************************************************************************/

int get_occurences(int i, int n)
{
	// 'i' position element in all sub-arrays
	return ((i + 1) * (n - 1));
}

int sansaXor(int arr_count, int* arr)
{
	int sum_xor = 0;

	// only add to sum for odd occurences
	for (int i = 0; i < arr_count; i++) {
		if (get_occurences(i, arr_count) % 2)
			sum_xor ^= arr[i];
	}

	return sum_xor;
}

int main()
{
	return 0;
}
