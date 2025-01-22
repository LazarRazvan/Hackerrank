/**
 * https://www.hackerrank.com/challenges/aor/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


/*****************************************************************************/
 
 /**
  * TODO
  */

/*****************************************************************************/

#define DIGIT_2_BIT(d, x)		(uint8_t)(((d) & (1 << (x))) >> (x))

#define BIT_SET(d, x)			((d) |= (1 << (x)))
#define BIT_UNSET(d, x)			((d) &= ~(1 << (x)))


/*****************************************************************************/

static uint8_t __digit_2_uint8(char hex)
{
	if (hex >= '0' && hex <= '9') {
		return (uint8_t)(hex - '0');
	} else if (hex >= 'A' && hex <= 'F') {
		return (uint8_t)(hex - 'A' + 10);
	} else if (hex >= 'a' && hex <= 'f') {
		return (uint8_t)(hex - 'a' + 10);
	} else {
		assert(0);
	}
}


static char __uint8_2_digit(uint8_t value)
{
	if (value <= 9) {
		return (char)('0' + value);
	} else if (value <= 15) {
		return (char)('A' + (value - 10));
	} else {
		assert(0);
	}
}

void aOrB(int k, char* a, char* b, char* c)
{
	int i, bit;
	bool leading_zero;
	uint8_t digit_a, digit_b, digit_c;
	uint8_t bit_a, bit_b, bit_c, k_ab;

	/****************************************************************
	 * A, B, C must have the same length.
	 ***************************************************************/
	if ((strlen(a) != strlen(b)) || (strlen(a) != strlen(c)))
		goto error;

	/****************************************************************
	 * First iteration to switch wrong bits and track correct bits
	 * that may be later updated to minimize the result.
	 ***************************************************************/
	i = 0;
	k_ab = 0;

	for (i = 0; i < strlen(a); i++) {
		digit_a = __digit_2_uint8(a[i]);
		digit_b = __digit_2_uint8(b[i]);
		digit_c = __digit_2_uint8(c[i]);

		if ((digit_a | digit_b) == digit_c)
			continue;

		for (bit = 3; bit >= 0; bit--) {
			bit_a = DIGIT_2_BIT(digit_a, bit);
			bit_b = DIGIT_2_BIT(digit_b, bit);
			bit_c = DIGIT_2_BIT(digit_c, bit);

			if ((bit_a | bit_b) == bit_c)
				continue;

			/*******************************************************
			 * Wrong bits.
			 *
			 * 1. bit_c = 0
			 * 1.1 bit_a = 0 | bit_b = 1	(switch bit_b)
			 * 1.2 bit_a = 1 | bit_b = 0	(switch bit_a)
			 * 1.3 bit_a = 1 | bit_b = 1	(switch bit_a and bit_b).
			 *
			 * 2. bit_c = 1
			 * 2.1 bit_a = 0 | bit_b = 0	(switch bit_b to min a)
			 *******************************************************/
			switch (bit_c) {
			case 0:
				if ((bit_a == 1) && (++k_ab > k))
					goto error;

				if ((bit_b == 1) && (++k_ab > k))
					goto error;

				BIT_UNSET(digit_a, bit);
				BIT_UNSET(digit_b, bit);

				break;
			case 1:
				if ((++k_ab > k))
					goto error;

				BIT_SET(digit_b, bit);

				break;
			default:
				goto error;
			}
		}

		// restore values in a and b
		a[i] = __uint8_2_digit(digit_a);
		b[i] = __uint8_2_digit(digit_b);
	}

	/****************************************************************
	 * If there are still remaining possibilities, we go back trying
	 * to minimize the results.
	 *
	 * 1. bit_c = 1
	 * 1.2 bit_a = 1 | bit_b = 0	-> bit_a = 0, bit_b = 1
	 * 1.3 bit_a = 1 | bit_b = 1	-> bit_a = 0
	 ***************************************************************/
	for (i = 0; i < strlen(a); i++) {
		digit_a = __digit_2_uint8(a[i]);
		digit_b = __digit_2_uint8(b[i]);
		digit_c = __digit_2_uint8(c[i]);

		for (bit = 3; bit >= 0; bit--) {
			bit_a = DIGIT_2_BIT(digit_a, bit);
			bit_b = DIGIT_2_BIT(digit_b, bit);
			bit_c = DIGIT_2_BIT(digit_c, bit);

			if (!bit_c)
				continue;

			//
			if (bit_a == 1 && bit_b == 0) {
				if (k_ab + 2 > k)
					continue;	// hope for 1|1 to switch single bit

				k_ab += 2;
				BIT_UNSET(digit_a, bit);
				BIT_SET(digit_b, bit);
			}

			if (bit_a == 1 && bit_b == 1) {
				if (k_ab + 1 > k) {
					a[i] = __uint8_2_digit(digit_a);
					b[i] = __uint8_2_digit(digit_b);

					goto print;	// there is nothing more we can do
				}

				k_ab++;
				BIT_UNSET(digit_a, bit);
			}
		}

		a[i] = __uint8_2_digit(digit_a);
		b[i] = __uint8_2_digit(digit_b);
	}

print:
	// print and skip leading 0 bytes
	leading_zero = true;
	for (i = 0; i < strlen(a); i++) {
		if (a[i] == '0' && leading_zero)
			continue;

		if (a[i] != '0')
			leading_zero = false;

		printf("%c", a[i]);
	}
	if (leading_zero)
		printf("0");
	printf("\n");

	leading_zero = true;
	for (i = 0; i < strlen(a); i++) {
		if (b[i] == '0' && leading_zero)
			continue;

		if (b[i] != '0')
			leading_zero = false;

		printf("%c", b[i]);
	}
	if (leading_zero)
		printf("0");
	printf("\n");

	return;

error:
	printf("-1\n");
}

int main()
{
	return 0;
}
