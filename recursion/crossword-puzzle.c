/**
 * https://www.hackerrank.com/challenges/crossword-puzzle/problem
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

#define MAX_TOKENS					100
#define DELIMITER					";"

#define DEF_SIZE					10

#define RIGHT_REGEX					0
#define DOWN_REGEX					1


/*****************************************************************************/

typedef struct regex_s {

	uint8_t		len;
	uint8_t		dir;
	uint8_t		start;
	char		s[DEF_SIZE];

} regex_t;


/*****************************************************************************/

//
// REGEX
//

static inline bool __regex_init(char **a, int i, int j, regex_t *r)
{
	//
	r->len = 0;

	/****************************************************************
	 * Right pattern
	 ***************************************************************/
	if (j + 1 < DEF_SIZE && a[i][j + 1] == '-') {
		r->dir = RIGHT_REGEX;

		//
		while (j >= 0 && a[i][j] != '+')
			j--;

		//
		j++; r->start = j;
		while (j < DEF_SIZE && a[i][j] != '+') {
			r->s[r->len++] = (a[i][j] == '-') ? 0 : a[i][j];
			j++;
		}

		return true;
	}

	/****************************************************************
	 * Down pattern
	 ***************************************************************/
	if (i + 1 < DEF_SIZE && a[i + 1][j] == '-') {
		r->dir = DOWN_REGEX;

		//
		while (i >= 0 && a[i][j] != '+')
			i--;

		//
		i++; r->start = i;
		while (i < DEF_SIZE && a[i][j] != '+') {
			r->s[r->len++] = (a[i][j] == '-') ? 0 : a[i][j];
			i++;
		}

		return true;
	}

	return false;
}


/*****************************************************************************/

//
// TOKENS
//

static char *tokens[MAX_TOKENS];
static int8_t mask[MAX_TOKENS];
static int tokens_len;

static inline void __tokens_init(char *words)
{
	char *p;

	//
	tokens_len = 0;

	//
	p = strtok(words, DELIMITER);
	while (p) {
		tokens[tokens_len++] = strdup(p);
		p = strtok(NULL, DELIMITER);
	}

	//
	memset(mask, 0, sizeof(mask));
}

static inline void __tokens_free(void)
{
	for (int i = 0; i < tokens_len; i++)
		free(tokens[i]);
}

static inline bool __tokens_full(void)
{
	for (int i = 0; i < tokens_len; i++)
		if (!mask[i])
			return false;

	return true;
}

static inline bool __token_is_match(int token_idx, regex_t *r)
{
	int i;
	char *token;

	token = tokens[token_idx];

	/****************************************************************
	 * Unused token, same length and matching regex.
	 ***************************************************************/
	//
	if (mask[token_idx] || r->len != strlen(token))
		return false;

	//
	for (i = 0; i < r->len; i++) {
		if (r->s[i] && token[i] != r->s[i])
			break;
	}

	return (i == r->len);
}

static inline void __token_set(char **a, int l, int c, int token_idx, regex_t *r)
{
	int i;
	char *token;

	token = tokens[token_idx];

	/****************************************************************
	 * Mark token as used and write it into matrix.
	 ***************************************************************/
	mask[token_idx] = 1;

	//
	switch (r->dir) {
	case RIGHT_REGEX:
		for (i = 0; i < r->len; i++)
			a[l][r->start + i] = token[i];

		break;
	case DOWN_REGEX:
		for (i = 0; i < r->len; i++)
			a[r->start + i][c] = token[i];

		break;
	default:
		assert(0);
		break;
	}
}

static inline void __token_unset(int token_idx)
{
	/****************************************************************
	 * Mark token as unused.
	 ***************************************************************/
	mask[token_idx] = 0;
}


/*****************************************************************************/

static bool __recursion(char **crossword)
{
	regex_t r;
	int i, j, k;

	/****************************************************************
	 * Stop recursion when all tokens are used.
	 ***************************************************************/
	if (__tokens_full())
		return true;

	/****************************************************************
	 * Iterate in matrix until '-' is found.
	 ***************************************************************/
	for (i = 0; i < DEF_SIZE; i++) {
		for (j = 0; j < DEF_SIZE; j++) {
			//
			if (crossword[i][j] != '-')
				continue;

			/*******************************************************
			 * Build regex and lookup for a matching token. For any
			 * matching token, continue recursion. On error, set
			 * token unused and continue lookup.
			 *******************************************************/
			if (!__regex_init(crossword, i, j, &r))
				return false;

			//
			for (k = 0; k < tokens_len; k++) {
				if (!__token_is_match(k, &r))
					continue;

				//
				__token_set(crossword, i, j, k, &r);

				//
				if (!__recursion(crossword)) {
					__token_unset(k); continue;
				}

				//
				return true;
			}
		}
	}

	return true;
}

char** crosswordPuzzle(int crossword_count, char** crossword, char* words,
					int* result_count)
{
	//
	__tokens_init(words);

	//
	if (!__recursion(crossword))
		goto finish;

	//
	*result_count = DEF_SIZE;

finish:
	__tokens_free();
	return crossword;
}


/*****************************************************************************/

int main()
{
	int rv, count;
	char **crossword, **result;
	char words[MAX_TOKENS];

	//
	rv = EXIT_SUCCESS;

	//
	crossword = (char **)malloc(10 * sizeof(char*));
	if (!crossword) {
		rv = EXIT_FAILURE; goto finish;
	}

	// TEST1
#if 0
	strcpy(words, "LONDON;DELHI;ICELAND;ANKARA");
	crossword[0] = strdup("+-++++++++");
	crossword[1] = strdup("+-++++++++");
	crossword[2] = strdup("+-++++++++");
	crossword[3] = strdup("+-----++++");
	crossword[4] = strdup("+-+++-++++");
	crossword[5] = strdup("+-+++-++++");
	crossword[6] = strdup("+++++-++++");
	crossword[7] = strdup("++------++");
	crossword[8] = strdup("+++++-++++");
	crossword[9] = strdup("+++++-++++");
#endif

	// TEST2
#if 0
	strcpy(words, "AGRA;NORWAY;ENGLAND;GWALIOR");
	crossword[0] = strdup("+-++++++++");
	crossword[1] = strdup("+-++++++++");
	crossword[2] = strdup("+-------++");
	crossword[3] = strdup("+-++++++++");
	crossword[4] = strdup("+-++++++++");
	crossword[5] = strdup("+------+++");
	crossword[6] = strdup("+-+++-++++");
	crossword[7] = strdup("+++++-++++");
	crossword[8] = strdup("+++++-++++");
	crossword[9] = strdup("++++++++++");
#endif

	// TEST3
#if 1
	strcpy(words, "CALIFORNIA;NIGERIA;CANADA;TELAVIV");
	crossword[0] = strdup("+-++++++++");
	crossword[1] = strdup("+-++-+++++");
	crossword[2] = strdup("+-------++");
	crossword[3] = strdup("+-++-+++++");
	crossword[4] = strdup("+-++-+++++");
	crossword[5] = strdup("+-++-+++++");
	crossword[6] = strdup("++++-+++++");
	crossword[7] = strdup("++++-+++++");
	crossword[8] = strdup("++++++++++");
	crossword[9] = strdup("----------");
#endif

	//
	result = crosswordPuzzle(DEF_SIZE, crossword, words, &count);
	if (!result) {
		rv = EXIT_FAILURE; goto free_crossword;
	}

	//
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			printf("%c ", result[i][j]);
		}
		printf("\n");
	}

free_crossword:
	for (int i = 0; i < DEF_SIZE; i++)
		free(crossword[i]);
	free(crossword);

finish:
	return rv;
}
