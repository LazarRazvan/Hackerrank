/**
 * https://www.hackerrank.com/challenges/winning-lottery-ticket/problem
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
 * Since there are only 10 digits [0-9], we can represent each ticket as a
 * bitmask where each bit indicates the presence of a digit in the ticket.
 *
 * Using these bitmasks, we store the frequency of each unique bitmask in an
 * array.
 *
 * To determine the winning ticket pairs, we iterate over the frequency array
 * and check pairs of bitmasks. If the bitwise OR (|) of two bitmasks contains
 * all digits (i.e., forms the bitmask 1111111111), they form a winning pair of
 * tickets.
 */

/*****************************************************************************/

#define MASK_SIZE				(1 << 10)
#define MASK_FULL				(uint16_t)(MASK_SIZE - 1)

#define CHR_2_DIGIT(c)			(uint16_t)((c) - '0')


/*****************************************************************************/

static void __init_freq(int tickets_count, char **tickets, int *freq)
{
	int i, j, mask;

	//
	for (i = 0; i < tickets_count; i++) {
		mask = 0;

		for (j = 0; j < strlen(tickets[i]); j++) {
			// stop processing if all digits are found
			if (!(mask ^ MASK_FULL))
				break;

			// set associated digit bit in mask
			mask |= 1 << CHR_2_DIGIT(tickets[i][j]);
		}

		freq[mask]++;
	}
}


static long __process_freq(int *freq)
{
	int i, j;
	long res = 0;

	//
	for (i = 0; i < MASK_SIZE; i++) {
		for (j = i; j < MASK_SIZE; j++) {
			if ((i | j) == MASK_FULL) {
				if (i != j)
					res += (long)freq[i] * freq[j];
				else
					res += (long)freq[i] * (freq[i] - 1) / 2;
			}
		}
	}

	return res;
}

/*****************************************************************************/

long winningLotteryTicket(int tickets_count, char** tickets)
{
	int freq[MASK_SIZE] = { 0 };

	/****************************************************************
	 * Convert tickets mask frequencies.
	 ***************************************************************/
	__init_freq(tickets_count, tickets, freq);

	/****************************************************************
	 * Process winning tickets.
	 ***************************************************************/
	return __process_freq(freq);
}

int main()
{
	char *tickets[] = {"129300455", "5559948277", "012334556", "56789", "123456879"};

	printf("%ld\n", winningLotteryTicket(5, tickets));

	return 0;
}
