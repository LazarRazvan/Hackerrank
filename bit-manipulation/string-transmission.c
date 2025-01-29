/**
 * https://www.hackerrank.com/challenges/string-transmission/problem
 * Copyright (C) 2024 Lazar Razvan.
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
 * TODO
 */

/*****************************************************************************/

static inline bool __is_periodic(char *s)
{
	int i, j, s_len;

	//
	s_len = strlen(s);
	for (i = 1; i < s_len; i++) {
		// must be a divisor
		if (s_len % i)
			continue;

		//
		for (j = i; j < s_len; j += i) {
			if (strncmp(s, s + j, i))
				break;
		}

		//
		if (j == s_len)
			return true;
	}

	return false;
}

static inline int *__get_divisors(int n, int *len)
{
	int *divisors;

	//
	*len = 0;
	divisors = (int *)malloc(sqrt(n) * sizeof(int));
	if (!divisors)
		return NULL;

	//
	divisors[(*len)++] = 1;

	//
	for (int i = 2; i < sqrt(n); i++) {
		if (n % i == 0) {
			divisors[(*len)++] = i;

			if (i != n / i)
				divisors[(*len)++] = n / i;
		}
	}

	return divisors;
}

static inline uint64_t __binomial_coefficient(int n, int k)
{
	uint64_t res;

	//
	if (k > n)
		return 0;

	if (k == 0 || k == n)
		return 1;

	//
	res = 1;
	for (int i = 1; i <= k; i++) {
		res *= (n - i + 1);
		res /= i;
	}

	//
	return res;
}

static inline uint64_t __total_possibilities(int n, int k)
{
	uint64_t possibilities;

	//
	possibilities = (1ULL << n);

	//
	for (int i = k + 1; i <= n; i++)
		possibilities -= __binomial_coefficient(n, i);

	//
	return possibilities;
}


/*****************************************************************************/

static void __do_combination(int *tmp, char *s_flipped, char *s, int n, int k,
							int idx, int tmp_idx, uint64_t *periodic_num)
{
	// check periodic string
	if (tmp_idx == k) {
		//
		memcpy(s_flipped, s, n);
		s_flipped[n] = '\0';

		//
		for (int i = 0; i < k; i++)
			s_flipped[tmp[i]] ^= 1;

		*periodic_num += __is_periodic(s_flipped) ? 1 : 0;
	}

	// stop when reaching end of indexes
	if (idx == n)
		return;

	// add current index
	tmp[tmp_idx] = idx;
	__do_combination(tmp, s_flipped, s, n, k, idx + 1, tmp_idx + 1, periodic_num);

	// move to next index
	__do_combination(tmp, s_flipped, s, n, k, idx + 1, tmp_idx, periodic_num);
}

static uint64_t __total_periodic(int *divisors, int divisors_len, int n, int k,
								char *s)
{
	int *tmp;
	char *s_flipped;
	uint64_t periodic_num = 0;

	//
	tmp = (int *)malloc(k * sizeof(int));
	if (!tmp)
		goto finish;

	//
	s_flipped = (char *)malloc(n * sizeof(char));
	if (!s_flipped)
		goto free_tmp;

	//
	for (int i = 0; i < divisors_len; i++)
		__do_combination(tmp, s_flipped, s, n, divisors[i], 0, 0, &periodic_num);

	free(s_flipped);
free_tmp:
	free(tmp);
finish:
	return periodic_num;
}


/*****************************************************************************/

int stringTransmission(int k, char *s)
{
	uint64_t possibilities;
	int *divisors, divisors_len, n;

	/****************************************************************
	 * Compute total possible strings.
	 *
	 * 2^n - Sum(C(n, i)), where i = k + 1 to n
	 ***************************************************************/
	n = strlen(s);
	possibilities = __total_possibilities(n, k);

	/****************************************************************
	 * TODO
	 ***************************************************************/
	divisors = __get_divisors(n, &divisors_len);
	if (!divisors)
		goto error;

	//
	if (__is_periodic(s))
		possibilities -= (k == n) ? 2 : 1;

	// n - not prime
	possibilities -= __total_periodic(divisors, divisors_len, n, k, s);

finish:
	free(divisors);

	return possibilities;

error:
	return -1;
}


/*****************************************************************************/

int main()
{
	printf("%d\n", stringTransmission(0, "00000"));
	return 0;
}
