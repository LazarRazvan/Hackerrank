/**
 * https://www.hackerrank.com/challenges/changing-bits/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/*****************************************************************************/

/**
 * Implementation Overview:
 *
 * - An array ("c") is maintained to track the carry bit for each position.
 * - The carry for the least significant bit (LSB) is always 0.
 * - The carry array is recomputed only when a "get_c" query is received and
 *   either "a" or "b" has been updated (tracked via a "dirty" flag).
 * - To optimize the recomputation of the carry array:
 *   1. Track the minimum ("min") and maximum ("max") bit positions updated.
 *   2. Iterate through the interval "[min, max]", updating the carry array.
 *   3. Stop iterating early if no further changes to the carry bits are
 *   detected, ensuring all bits in the range are updated correctly.
 */


/*****************************************************************************/

//
#define CHR_2_DIGIT(c)			(uint8_t)((c) & 1)
#define DIGIT_2_CHR(d)			(char)((d) | '0')

//
#define IDX_2_MSB(i, n)			(int)((n) - (i) - 1)

//
#define CARRY(a, b, c)			((((a) | (b)) & (c)) | ((a) & (b)))

//
#define TRIGGER_SET(d, min, max, idx)	\
	do {								\
		d = true;						\
		min = idx < min ? idx : min;	\
		max = idx > max ? idx : max;	\
	} while (0)							\

#define TRIGGER_CLR(d, min, max)		\
	do {								\
		d = false;						\
		min = INT_MAX;					\
		max = INT_MIN;					\
	} while (0)							\


/*****************************************************************************/

static inline void
__init(char *a, char *b, uint8_t *aint, uint8_t *bint, uint8_t *c, int len)
{
	/****************************************************************
	 * Convert characters to digit for the ease of computation and
	 * pad at MSB with 0.
	 ***************************************************************/
	 aint[0] = 0;
	 bint[0] = 0;
	 for (int i = 0; i < len; i++) {
		aint[i + 1] = CHR_2_DIGIT(a[i]);
		bint[i + 1] = CHR_2_DIGIT(b[i]);
	 }

	/****************************************************************
	 * Init carry array for each bit position from LSB to MSB. Carry
	 * on LSB will always be 0.
	 *
	 * a:   0 0 0 1
	 * b:   1 1 1 1
	 * c: 1 1 1 1 0
	 ***************************************************************/
	c[len] = 0;

	for (int i = len - 1; i >= 0; i--)
		c[i] = CARRY(aint[i + 1], bint[i + 1], c[i + 1]);
}

static inline void
__carry(uint8_t *a, uint8_t *b, uint8_t *c, int min, int max)
{
	uint8_t new;

	/****************************************************************
	 * Start from LSB bit updated, start updating carry array until
	 * previous value is not changed. Make sure the iteration reach
	 * to MSB bit updated.
	 ***************************************************************/
	for (int i = max - 1; i >= 0; i--) {
		new = CARRY(a[i + 1], b[i + 1], c[i + 1]);

		if (new == c[i] && i < min)
			break;

		c[i] = CARRY(a[i + 1], b[i + 1], c[i + 1]);
	}
}

void changeBits(char* a, char* b, int queries_count, char** queries)
{
	char *q;
	bool dirty;
	char cmd[10];
	uint8_t *aint, *bint, *c;
	int x, idx, len, min, max, msb_idx, q_idx;

	//
	len = strlen(a);

	/****************************************************************
	 * Memory allocation for queries buffer, carry array and each
	 * a and b strings for integer values.
	 ***************************************************************/
	aint = (uint8_t *)malloc((len + 1) * sizeof(uint8_t));
	if (!aint)
		goto finish;

	bint = (uint8_t *)malloc((len + 1) * sizeof(uint8_t));
	if (!bint)
		goto aint_free;

	c = (uint8_t *)malloc((len + 1) * sizeof(uint8_t));
	if (!c)
		goto bint_free;

	q = (char *)malloc((queries_count + 1) * sizeof(char));
	if (!q)
		goto c_free;


	//
	q_idx = 0;
	__init(a, b, aint, bint, c, len);

	//
	TRIGGER_CLR(dirty, min, max);

	/****************************************************************
	 * Run all querries.
	 ***************************************************************/
	for (int i = 0; i < queries_count; i++) {
		sscanf(queries[i], "%s", cmd);

		if (cmd[4] == 'a') {
			sscanf(queries[i] + 5, "%d %d", &idx, &x);

			msb_idx = IDX_2_MSB(idx, len + 1);
			aint[msb_idx] = x;

			TRIGGER_SET(dirty, min, max, msb_idx);
			continue;
		}

		if (cmd[4] == 'b') {
			sscanf(queries[i] + 5, "%d %d", &idx, &x);

			msb_idx = IDX_2_MSB(idx, len + 1);
			bint[msb_idx] = x;

			TRIGGER_SET(dirty, min, max, msb_idx);
			continue;
		}

		if (cmd[4] == 'c') {
			sscanf(queries[i] + 5, "%d", &idx);

			msb_idx = IDX_2_MSB(idx, len + 1);
			if (dirty) {
				__carry(aint, bint, c, min, max);
				TRIGGER_CLR(dirty, min, max);
			}

			q[q_idx++] = DIGIT_2_CHR(aint[msb_idx] ^ bint[msb_idx] ^ c[msb_idx]);
		}
	}

	/****************************************************************
	 * Print result.
	 ***************************************************************/
	q[q_idx] = '\0';
	printf("%s", q);

	free(q);
c_free:
	free(c);
bint_free:
	free(bint);
aint_free:
	free(aint);
finish:
	return;
}


int main()
{
	return 0;
}
