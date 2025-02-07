/**
 * https://www.hackerrank.com/challenges/queue-using-two-stacks/problem
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
 * Make enqueue opeartion costly.
 *
 * For each enqeue, pop all elements from stack1 and push to stack2. Push the
 * new element to stack1 and move all elements from stack2 back to stack1.
 */

/*****************************************************************************/

//
// Stack implementation
//

#define STACK_SIZE					100000

typedef struct stack_s {

	int					*h;					// head
	int					buf[STACK_SIZE];	// storage

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

static inline int __stack_push(stack_t *s, int data)
{
	if (__stack_is_full(s))
		return 1;

	*(s->h)++ = data;

	return 0;
}

static inline int __stack_pop(stack_t *s, int *data)
{
	if (__stack_is_empty(s))
		return 1;

	*data = *--(s->h);

	return 0;
}

static inline int __stack_top(stack_t *s, int *data)
{
	if (__stack_is_empty(s))
		return 1;

	*data = *(s->h - 1);

	return 0;
}

static inline void __stack_print(stack_t *s)
{
	int *it;

	for (it = s->buf; it < s->h; it++)
		printf("%d ", *it);

	printf("\n");
}


/*****************************************************************************/

//
// Queue implementation with two stacks
//

static inline void __enqueue(stack_t *s1, stack_t *s2, int data)
{
	int tmp;

	// pop all elements from s1 and push to s2
	assert(__stack_is_empty(s2));

	while (!__stack_is_empty(s1)) {
		assert(!__stack_pop(s1, &tmp));
		assert(!__stack_push(s2, tmp));
	}

	// push current element to s1
	assert(!__stack_push(s1, data));

	// pop all elements from s2 and push back to s1
	while (!__stack_is_empty(s2)) {
		assert(!__stack_pop(s2, &tmp));
		assert(!__stack_push(s1, tmp));
	}
}

static inline void __dequeue(stack_t *s1)
{
	int tmp;

	// pop element from s1
	assert(!__stack_pop(s1, &tmp));
}

static inline int __top(stack_t *s1)
{
	int tmp;

	// pop element from s1
	assert(!__stack_top(s1, &tmp));

	return tmp;
}


/*****************************************************************************/

int main()
{
	stack_t s1, s2;
	int q, type, val;

	// init stacks
	__stack_init(&s1);
	__stack_init(&s2);

	// read number of querries
	scanf("%d", &q);

	// perform each querry
	for (int i = 0; i < q; i++) {
		scanf("%d", &type);

		switch (type) {
		case 1:
			scanf("%d", &val);
			__enqueue(&s1, &s2, val);
			break;
		case 2:
			__dequeue(&s1);
			break;
		case 3:
			printf("%d\n", __top(&s1));
			break;
		default:
			return -1;
		}
	}

	return 0;
}
