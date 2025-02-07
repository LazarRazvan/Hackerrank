/**
 * https://www.hackerrank.com/challenges/is-binary-search-tree/problem
 * Copyright (C) 2025 Lazar Razvan.
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
 * Use a stack. For each open bracket, push to stack. For each closed bracket
 * the top of the stack should be a pair of it.
 */

/*****************************************************************************/

//
// Stack implementation
//

#define STACK_SIZE					1001

typedef struct stack_s {

	char				*h;					// head
	char				buf[STACK_SIZE];	// storage

} stack_t;


static inline void __stack_init(stack_t *s)
{
	s->h = s->buf;
}

static inline int __stack_is_full(stack_t *s)
{
	return (s->h == s->buf + STACK_SIZE);
}

static inline int __stack_is_empty(stack_t *s)
{
	return (s->h == s->buf);
}

static inline int __stack_push(stack_t *s, char data)
{
	if (__stack_is_full(s))
		return 1;

	*(s->h)++ = data;

	return 0;
}

static inline int __stack_pop(stack_t *s, char *data)
{
	if (__stack_is_empty(s))
		return 1;

	*data = *--(s->h);

	return 0;
}

static inline int __stack_top(stack_t *s, char *data)
{
	if (__stack_is_empty(s))
		return 1;

	*data = *(s->h - 1);

	return 0;
}


/*****************************************************************************/

char* isBalanced(char* s)
{
	char c;
	stack_t st;

	//
	__stack_init(&st);

	//
	for (int i = 0; i < strlen(s); i++) {
		switch (s[i]) {
		case '(':
		case '[':
		case '{':
			assert(!__stack_push(&st, s[i]));
			break;
		case ')':
			if (__stack_pop(&st, &c) || c != '(')
				return "NO";
			break;
		case '}':
			if (__stack_pop(&st, &c) || c != '{')
				return "NO";
			break;
		case ']':
			if (__stack_pop(&st, &c) || c != '[')
				return "NO";
			break;
		default:
			return "NO";
		}
	}

	return __stack_is_empty(&st) ? "YES" : "NO";
}


/*****************************************************************************/

int main()
{
	int n;
	char s[1001];

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		printf("%s\n", isBalanced(s));
	}

	return 0;
}
