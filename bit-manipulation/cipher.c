/**
 * https://www.hackerrank.com/challenges/cipher/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************************************************/
 
 /**
 * Explanation of the algorithm:
 *
 * Let 'bx' represent the bit at position x in the original message, and 'sx'
 * represent the bit at position x in the encrypted message.
 *
 * Example alignment:
 * Original message:  b0  b1  b2  ...  bn
 * Shifted rows:      0   b0  b1  ...  bn-1 bn
 *                    0   0   b0  ...  bn-2 bn-1 bn
 *                    ...
 * ----------------------------------------------
 * Encrypted message: s0  s1  s2  ...  sn+k-3 sn+k-2 sn+k-1
 *
 * Steps:
 * 1) For the part where zero bits are padded due to shifting, the relationship
 * is:
 *    b0                = s0
 *    b1 XOR b2         = s1
 *    ...
 *    In general:
 *    bi = si XOR (b0 XOR b1 XOR ... XOR b[i-1])
 *
 * 2) For the part where the shifted rows are fully aligned, the relationship is:
 *    b2 XOR b1 XOR b0  = s2
 *    b3 XOR b2 XOR b1  = s3
 *    b4 XOR b3 XOR b2  = s4
 *    ...
 *    In general:
 *    bi = si XOR (s[i-1] XOR b[i-k])
 */

/*****************************************************************************/

#define DIGIT_2_BIT(c)			(uint8_t)((c) - '0')
#define BIT_2_DIGIT(b)			(char)((b) + '0')


/*****************************************************************************/

char* cipher(int k, char* s)
{
	int i, n;
	uint8_t aux;
	char *result;

	// stop computation for no shifting
	if (k == 1)
		return s;

	//
	n = strlen(s) - k + 1;

	// do not perform extra computation (there will only be zeroes)
	if (k > n)
		k = n;

	// result buffer (include NULL)
	result = (char *)malloc((n + 1) * sizeof(char));
	if (!result)
		return NULL;

	result[n] = '\0';

	// first bit in result is always the same as in crypted message
	result[0] = s[0];

	// incomplete message
	aux = DIGIT_2_BIT(s[0]);

	for (i = 1; i < k; i++) {
		result[i] = BIT_2_DIGIT(DIGIT_2_BIT(s[i]) ^ aux);
		aux ^= DIGIT_2_BIT(result[i]);
	}

	// complete message
	for (i = k; i < n; i++) {
		aux = DIGIT_2_BIT(s[i-1]) ^ DIGIT_2_BIT(result[i - k]);
		result[i] = BIT_2_DIGIT(DIGIT_2_BIT(s[i]) ^ aux);
	}

	free(result);

	return result;
}

int main()
{
	return 0;
}
