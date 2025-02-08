/**
 * https://www.hackerrank.com/challenges/simple-text-editor/problem?
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
 * Implement text editor currrent data using a stack.
 *
 * To perform undo operations, use a stack of previous events and a stack to
 * track delete operations. The undo of a delete operations represent moving
 * characters from delete operations stack back to editor stack.
 */
/*****************************************************************************/

#define STACK_SIZE					1000000


/*****************************************************************************/

//
// Text stack implementation
//

typedef struct text_stack_s {

	char				*h;					// head
	char				buf[STACK_SIZE];	// storage

} text_stack_t;


static inline void __text_stack_init(text_stack_t *s)
{
	s->h = s->buf;
}

static inline int __text_stack_is_full(text_stack_t *s)
{
	return (s->h == s->buf + STACK_SIZE);
}

static inline int __text_stack_is_empty(text_stack_t *s)
{
	return (s->h == s->buf);
}

static inline int __text_stack_push(text_stack_t *s, char data)
{
	if (__text_stack_is_full(s))
		return 1;

	*(s->h)++ = data;

	return 0;
}

static inline int __text_stack_pop(text_stack_t *s, char *data)
{
	if (__text_stack_is_empty(s))
		return 1;

	*data = *--(s->h);

	return 0;
}

static inline int __text_stack_top(text_stack_t *s, int *data)
{
	if (__text_stack_is_empty(s))
		return 1;

	*data = *(s->h - 1);

	return 0;
}

static inline void __text_stack_print(text_stack_t *s)
{
	char *it;

	for (it = s->buf; it < s->h; it++)
		printf("%c ", *it);

	printf("\n");
}


/*****************************************************************************/

//
// Operation stack implementation
//

//
typedef enum op_id_s {

	OP_APPEND,
	OP_DELETE,

} op_id;

//
typedef struct op_s {

	op_id				type;				// action type
	int					len;				// action length

} op_t;

//
typedef struct op_stack_s {

	op_t				*h;					// head
	op_t				buf[STACK_SIZE];	// storage

} op_stack_t;


static inline void __op_stack_init(op_stack_t *s)
{
	s->h = s->buf;
}

static inline int __op_stack_is_full(op_stack_t *s)
{
	return (s->h == s->buf + STACK_SIZE);
}

static inline int __op_stack_is_empty(op_stack_t *s)
{
	return (s->h == s->buf);
}

static inline int __op_stack_push(op_stack_t *s, op_t *data)
{
	if (__op_stack_is_full(s))
		return 1;

	*(s->h)++ = *data;

	return 0;
}

static inline int __op_stack_pop(op_stack_t *s, op_t *data)
{
	if (__op_stack_is_empty(s))
		return 1;

	*data = *--(s->h);

	return 0;
}

static inline void __op_stack_print(op_stack_t *s)
{
	op_t *it;

	for (it = s->buf; it < s->h; it++)
		printf("%s %d\n", it->type == OP_APPEND ? "APPEND" : "DELETE", it->len);

	printf("\n");
}


/*****************************************************************************/

//
// Operations implementation
//
static void __op_append(text_stack_t *editor, op_stack_t *ops, char *s)
{
	op_t op;

	/****************************************************************
	 * Push characters in editor stack and register append action.
	 ***************************************************************/
	//
	for (int i = 0; i < strlen(s); i++)
		assert(!__text_stack_push(editor, s[i]));

	//
	op.type = OP_APPEND;
	op.len	= strlen(s);
	assert(!__op_stack_push(ops, &op));
}

static void __op_delete(text_stack_t *editor, text_stack_t *undo,
						op_stack_t *ops, int k)
{
	char c;
	op_t op;

	/****************************************************************
	 * Pop characters from editor and push to undo stack (in case of
	 * undo). Register delete action.
	 ***************************************************************/
	//
	for (int i = 0; i < k; i++) {
		assert(!__text_stack_pop(editor, &c));
		assert(!__text_stack_push(undo, c));
	}

	//
	op.type = OP_DELETE;
	op.len	= k;
	assert(!__op_stack_push(ops, &op));
}

static void __op_print(text_stack_t *editor, int k)
{
	/****************************************************************
	 * Nothing to do if k is higher than had.
	 ***************************************************************/
	k--;
	if (k > editor->h - editor->buf)
		return;

	printf("%c\n", editor->buf[k]);
}

static void __op_undo(text_stack_t *editor, text_stack_t *undo,
					op_stack_t *ops)
{
	int i;
	char c;
	op_t op;

	/****************************************************************
	 * Nothing to do if no action in stack.
	 ***************************************************************/
	if (__op_stack_pop(ops, &op))
		return;

	/****************************************************************
	 * APPEND undo:
	 * 	Pop n characters from editor stack.
	 *
	 * DELETE undo:
	 *  Pop n characters from undo stack and push back to editor.
	 ***************************************************************/
	switch (op.type) {
	case OP_APPEND:
		for (i = 0; i < op.len; i++)
			assert(!__text_stack_pop(editor, &c));

		break;
	case OP_DELETE:
		for (i = 0; i < op.len; i++) {
			assert(!__text_stack_pop(undo, &c));
			assert(!__text_stack_push(editor, c));
		}

		break;
	default:
		assert(0);
		break;
	}
}

/*****************************************************************************/

// Global variables due to stack size limit 8 MB
op_stack_t ops;
char buf[STACK_SIZE];
text_stack_t editor, undo;


/*****************************************************************************/

int main()
{
	int i, q, t, k;

	/****************************************************************
	 * Init editor, undo and events stack.
	 ***************************************************************/
	__op_stack_init(&ops);
	__text_stack_init(&undo);
	__text_stack_init(&editor);
	
	/****************************************************************
	 * Perform actions.
	 ***************************************************************/
	scanf("%d", &q);
	for (i = 0; i < q; i++) {
		scanf("%d", &t);

		switch (t) {
		case 1:
			scanf("%s", buf);
			__op_append(&editor, &ops, buf);
			break;
		case 2:
			scanf("%d", &k);
			__op_delete(&editor, &undo, &ops, k);
			break;
		case 3:
			scanf("%d", &k);
			__op_print(&editor, k);
			break;
		case 4:
			__op_undo(&editor, &undo, &ops);
			break;
		default:
			return -1;
		}
	}

	return 0;
}
