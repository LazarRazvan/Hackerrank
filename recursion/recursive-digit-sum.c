/**
 * https://www.hackerrank.com/challenges/recursive-digit-sum/problem
 * Copyright (C) 2025 Lazar Razvan.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


/*****************************************************************************/

#define CHR_2_DIGIT(c)			(int)((c) - '0')


/*****************************************************************************/

static uint64_t __recursion(uint64_t n)
{
	uint64_t sum = 0;

	//
	if (n < 10)
		return n;

	//
	while (n) {
		sum += n % 10;
		n /= 10;
	}

	return __recursion(sum);
}

int superDigit(char *n, int k)
{
	uint64_t sum = 0;

	/****************************************************************
	 * Maximum digits is:
	 *
	 * k * log10(n) = 10^5 * log10(10^100000) = 10^5 * 10^5 = 10^10.
	 *
	 * This means that for wors case (all digits are '9'), the entire
	 * sum fits into an uint64.
	 ***************************************************************/
	for (int i = 0; i < strlen(n); i++)
		sum += CHR_2_DIGIT(n[i]);

	sum *= k;

	return __recursion(sum);
}

/*****************************************************************************/

int main()
{
	printf("%d\n", superDigit("148", 3));

	return EXIT_SUCCESS;
}
