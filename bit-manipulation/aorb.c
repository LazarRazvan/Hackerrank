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

static inline uint8_t __hex_ch_to_uint8(char hex)
{
	if (hex >= '0' && hex <= '9') {
		return (uint8_t)(hex - '0');
	} else if (hex >= 'A' && hex <= 'F') {
		return (uint8_t)(hex - 'A' + 10);
	} else {
		assert(0);
	}
}

static inline uint8_t *__hex_str_to_uint8(char *s, int arr_len)
{
	int k = 0;
	uint8_t *arr = NULL;

	// 2 hex digit is one byte
	arr = (uint8_t *)malloc(arr_len * sizeof(uint8_t));
	if (!arr)
		goto finish;

	// convert 2 hex digits to one byte
	if (strlen(s) % 2) {
		k = 1;
		arr[0] = 0 << 4 | __hex_ch_to_uint8(s[0]);
	} else {
		arr[0] = __hex_ch_to_uint8(s[0]) << 4 | __hex_ch_to_uint8(s[1]);
	}

	for (int i = 1; i < arr_len; i++)
		arr[i] = __hex_ch_to_uint8(s[2*i-k]) << 4 | __hex_ch_to_uint8(s[2*i+1-k]);

finish:
	return arr;
}


/*****************************************************************************/

static int __fix_computation(uint8_t *a, uint8_t *b, uint8_t *c, int arr_len)
{
	int k = 0;
	int8_t bit;
	uint8_t dif, mask;

	for (int i = 0; i < arr_len; i++) {
		dif = (a[i] | b[i]) ^ c[i];

		//
		if (!dif)
			continue;

		//
		for (bit = 7; bit >= 0; bit--) {
			mask = 1 << bit;

			if (!(dif & mask))
				continue;

			// c = 0 -> a and b must be 0
			if (!(c[i] & mask)) {
				if (a[i] & mask) {
					a[i] &= ~mask; k++;
				}

				if (b[i] & mask) {
					b[i] &= ~mask; k++;
				}

				continue;
			}

			// c = 1 -> make b 0 to keep a minimum
			b[i] |= mask; k++;
		}
	}

	return k;
}

static void __min_computation(uint8_t *a, uint8_t *b, uint8_t *c, int arr_len,
							int k)
{
	int8_t bit;
	uint8_t mask;

	for (int i = 0; i < arr_len; i++) {
		//
		if (!c[i])
			continue;

		//
		for (bit = 7; bit >= 0; bit--) {
			mask = 1 << bit;

			if (!(c[i] & mask))
				continue;

			// a = 1, b = 1 => a = 0, b = 1
			if ((a[i] & mask) && (b[i] & mask)) {
				if (k - 1 < 0)
					return;

				a[i] &= ~mask; k--;
				continue;
			}

			// a = 0, b = 1 => a = 1, b = 0
			if ((a[i] & mask) && !(b[i] & mask)) {
				if (k - 2 < 0)
					continue;

				a[i] &= ~mask; b[i] |= mask; k -= 2;
			}
		}
	}
}

static void __print(uint8_t *a, uint8_t *b, int arr_len)
{
	bool leading_zero;

	// a
	leading_zero = true;
	for (int i = 0; i < arr_len; i++) {
		if (leading_zero) {
			if (!a[i])
				continue;

			leading_zero = false;
			printf("%X", a[i]);
			continue;
		}

		leading_zero = false;
		printf("%02X", a[i]);
	}

	if (leading_zero)
		printf("0\n");
	else
		printf("\n");

	// b
	leading_zero = true;
	for (int i = 0; i < arr_len; i++) {
		if (leading_zero) {
			if (!b[i])
				continue;

			leading_zero = false;
			printf("%X", b[i]);
			continue;
		}

		leading_zero = false;
		printf("%02X", b[i]);
	}

	if (leading_zero)
		printf("0\n");
	else
		printf("\n");
}


/*****************************************************************************/

void aOrB(int k, char* a, char* b, char* c)
{
	int arr_len, s_len;
	uint8_t *aint, *bint, *cint;

	//
	s_len = strlen(a);
	arr_len = s_len / 2 + s_len % 2;

	/****************************************************************
	 * Convert strings to uint8_t array.
	 ***************************************************************/
	aint = __hex_str_to_uint8(a, arr_len);
	if (!aint)
		goto finish;

	bint = __hex_str_to_uint8(b, arr_len);
	if (!bint)
		goto free_aint;

	cint = __hex_str_to_uint8(c, arr_len);
	if (!cint)
		goto free_bint;

	/****************************************************************
	 * Fix computation.
	 ***************************************************************/
	k -= __fix_computation(aint, bint, cint, arr_len);
	if (k < 0) {
		printf("-1\n");
		goto free_cint;
	}

	/****************************************************************
	 * Minimize a and b.
	 ***************************************************************/
	__min_computation(aint, bint, cint, arr_len, k);

	/****************************************************************
	 * Print.
	 ***************************************************************/
	__print(aint, bint, arr_len);

free_cint:
	free(cint);
free_bint:
	free(bint);
free_aint:
	free(aint);
finish:
	return;
}

int main()
{
	aOrB(25, "B631EB5AE", "601C227E1", "707AC8792");
	aOrB(12, "CAF7028FD", "59B5AC1CE", "CAF1B7B7F");
	aOrB(3, "81B9BB94E", "8AB3CA95E", "8BBBFB95E");

	return 0;
}
