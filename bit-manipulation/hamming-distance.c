/**
 * https://www.hackerrank.com/challenges/hamming-distance/problem
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


static inline void __clear(char *s, char ch, int l, int r)
{
	l--; r--;
	memset(s + l, ch, r - l + 1);
}

static inline void __reverse(char *s, int l, int r)
{
	char tmp;

	l--; r--;
	while (l < r) {
		tmp = s[l]; s[l] = s[r]; s[r] = tmp;
		l++; r--;
	}
}

static inline void __print(char *s, int l, int r)
{
	l--; r--;
	printf("%.*s\n", (r - l + 1), s + l);
}

static inline void __hamming(char *s, int l1, int l2, int len)
{
	int res;

	l1--; l2--;

	res = 0;
	for (int i = 0; i < len; i++)
		res += (s[l1 + i] == s[l2 + i]) ? 0 : 1;

	printf("%d\n", res);
}

static inline void __swap(char *s, int l1, int l2, int r1, int r2, int n)
{
	char *tmp;
	int len1, len2, dif;

	l1--; l2--; r1--; r2--;

	//
	len1 = r1 - l1 + 1;
	len2 = r2 - l2 + 1;

	//
	if (len1 == len2) {
		tmp = strndup(s + l1, len1);
		memcpy(s + l1, s + l2, len1);
		memcpy(s + l2, tmp, len1);
		free(tmp);

		return;
	}

	//
	dif = abs(len1 - len2);
	if (len1 < len2) {
		// move s1 (shorter) into s2 position (larger)
		tmp = strndup(s + l2, len2);
		memcpy(s + l2, s + l1, len1);

		// left shift (remove remaining s2 string)
		memmove(s + l2 + len1, s + r2 + 1, n - r2 -1);

		// right shift (ensure s2 fit in s1 position)
		n -= dif;
		memmove(s + r1 + dif + 1, s + r1 + 1, n - r1 - 1);

		// move s2 into s1 position
		memcpy(s + l1, tmp, len2);

		//
		free(tmp);
	} else {
		// move s2 (shorter) into s1 position (larger)
		tmp = strndup(s + l1, len1);
		memcpy(s + l1, s + l2, len2);

		// left shift (remove remaining s1 string)
		memmove(s + l1 + len2, s + r1 + 1, n - r1 -1);

		// right shift (ensure s1 fit in s2 position)
		n -= dif;
		r2 -= dif;
		l2 -= dif;
		memmove(s + r2 + 1 + (len1 - len2), s + r2 + 1, n - r2 - 1);

		// move s1 into s2 position
		memcpy(s + l2, tmp, len1);

		//
		free(tmp);
	}
}


/*****************************************************************************/

int main()
{
	char *s, c, ch;
	int n, m, l1, l2, r1, r2, len;

	//
	scanf("%d", &n);

	//
	s = (char *)malloc((n+1) * sizeof(char));
	if (!s)
		goto error;;

	scanf("%s", s);

	//
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf(" %c", &c);

		switch (c) {
		case 'C':
			scanf("%d %d %c", &l1, &r1, &ch);
			__clear(s, ch, l1, r1);
			break;
		case 'S':
			scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
			__swap(s, l1, l2, r1, r2, n);
			break;
		case 'R':
			scanf("%d %d", &l1, &r1);
			__reverse(s, l1, r1);
			break;
		case 'W':
			scanf("%d %d", &l1, &r1);
			__print(s, l1, r1);
			break;
		case 'H':
			scanf("%d %d %d", &l1, &l2, &len);
			__hamming(s, l1, l2, len);
			break;
		default:
			goto error;
		}
	}

//success:
	free(s);
	return EXIT_SUCCESS;

error:
	return EXIT_FAILURE;
}
