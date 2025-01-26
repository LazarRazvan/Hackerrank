/**
 * Combinations.
 *
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


/*****************************************************************************/

#define BITS_IN_TYPE(t)			(sizeof(t) * CHAR_BIT)
#define ARRAY_SIZE(a)			(sizeof(a) / sizeof(a[0]))


/*****************************************************************************/

/**
 * Alternative to count number of set bits in an integer.
 */

static inline int __custom_popcountll(int64_t x)
{
	int cnt = 0;

	for (; x > 0; cnt++)
		x = x & (x - 1);

	return cnt;
}

#if defined(__GNUC__) || defined(__clang__)
	#define popcount(x)		__builtin_popcountll(x)
#else
	#define popcount(x)		__custom_popcountll(x)
#endif


/*****************************************************************************/

/**
 * Perform all combinations using iterative approach (bitmasking).
 *
 * A valid combination of size "k" corresponds to a binary number with exactly
 * k bits set 1.
 *
 * Use this approach only for n smaller than sizeof int64_t (64 bits).
 */

static inline void __print_iterative(int64_t *arr, int64_t mask)
{
	printf("{");

	//
	for (uint8_t i = 0; i < BITS_IN_TYPE(int64_t); i++) {
		if (mask & (1LL << i))
			printf("%ld ", arr[i]);
	}

	//
	printf("}\n");
}

static void __iterative_combinations(int64_t *arr, int64_t n, int64_t k)
{
	for (int64_t i = 0; i < (1LL << n) - 1; i++) {
		if (popcount(i) == k)
			__print_iterative(arr, i);
	}
}


/*****************************************************************************/

/**
 * Perform all combinations using recursive approach.
 *
 * We need an extra buffer to store the combinations.
 */

static inline void __print_arr(int64_t *arr, int64_t n)
{
	printf("{");

	//
	for (int64_t i = 0; i < n; i++)
		printf("%ld ", arr[i]);

	//
	printf("}\n");
}

static void __recursive(int64_t *arr, int64_t *tmp, int64_t n, int64_t k,
						int64_t arr_idx, int64_t tmp_idx)
{
	// print and stop when reaching k elements
	if (tmp_idx == k) {
		__print_arr(tmp, tmp_idx);
		return;
	}

	// stop when reaching end of arr elements
	if (arr_idx == n)
		return;

	// add current element and move further
	tmp[tmp_idx] = arr[arr_idx];
	__recursive(arr, tmp, n, k, arr_idx + 1, tmp_idx + 1);

	// move further in arr elements
	__recursive(arr, tmp, n, k, arr_idx + 1, tmp_idx);
}

static void __recursive_combinations(int64_t *arr, int64_t n, int64_t k)
{
	int64_t *tmp;

	//
	tmp = (int64_t *)malloc(k * sizeof(int64_t));
	if (!tmp)
		return;

	//
	__recursive(arr, tmp, n, k, 0, 0);

	//
	free(tmp);
}


/*****************************************************************************/

void combinations(int64_t *arr, int64_t n, int64_t k)
{
	//
	if (k > n)
		return;
	//
	if (n < BITS_IN_TYPE(int64_t))
		__iterative_combinations(arr, n, k);
	else
		__recursive_combinations(arr, n, k);
}

int main()
{
	int64_t arr[] = {0, 1, 2, 3, 4, 5};

	for (int i = 0; i <= ARRAY_SIZE(arr); i++) {
		printf("C(%ld %d):\n", ARRAY_SIZE(arr), i);
		combinations(arr, ARRAY_SIZE(arr), i);
	}
}
