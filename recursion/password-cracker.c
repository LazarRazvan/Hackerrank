/**
 * https://www.hackerrank.com/challenges/password-cracker/problem
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
 * loginAttempt is <= 2000 so we can have at most 2000 passwords.
 */
#define MAX_PASSWORDS					2000
#define MAX_SPACES						1999
#define WRONG_PASSWORD					"WRONG PASSWORD"


/*****************************************************************************/

// Output buffer
static char buf[MAX_PASSWORDS + MAX_SPACES];

// Visited positions that return error (cannot find any matches)
static bool visited[MAX_PASSWORDS + 1];

// Passwords indexes that match the login attempt password
static uint8_t match[MAX_PASSWORDS];


/*****************************************************************************/

int __recursion(char *s, char **p, int s_idx, int p_cnt, int *m_idx)
{
	int i;
	char *pass;

	/****************************************************************
	 * Stop recursion when entire string is matched (success) or
	 * when current index was already processed without success.
	 ***************************************************************/
	if (!strlen(s))
		return 1;

	if (visited[s_idx])
		return 0;

	/****************************************************************
	 * Loop and continue recursion with any matching password.
	 ***************************************************************/
	for (i = 0; i < p_cnt; i++) {
		pass = p[i];
		if (strlen(pass) <= strlen(s) && !strncmp(pass, s, strlen(pass))) {

			//
			match[(*m_idx)++] = i;

			//
			if (__recursion(s + strlen(pass), p, s_idx + strlen(pass),
							p_cnt, m_idx))
				return 1;
		}
	}

	visited[s_idx] = 1;

	return 0;
}


/*****************************************************************************/

char* passwordCracker(int passwords_count, char** passwords, char* loginAttempt)
{
	int len, idx;

	//
	idx = 0;
	memset(visited, 0, sizeof(visited));

	//
	idx = 0;
	if (!__recursion(loginAttempt, passwords, 0, passwords_count, &idx)) {
		strcpy(buf, WRONG_PASSWORD);
	} else {
		len = 0;

		//
		for (int i = 0; i < idx; i++) {
			strcpy(buf + len, passwords[match[i]]);
			len += strlen(passwords[match[i]]);
			buf[len++] = ' ';
		}

		//
		buf[len - 1] = '\0';
	}

	return buf;
}


/*****************************************************************************/

int main()
{
	char **passwords;
	int rv = EXIT_SUCCESS;

#if 0
	passwords = (char **)malloc(6 * sizeof(char*));
	if (!passwords) {
		rv = EXIT_FAILURE; goto finish;
	}
	passwords[0] = strdup("alutwfal");
	passwords[1] = strdup("kkhbqlrxnm");
	passwords[2] = strdup("qyyx");
	passwords[3] = strdup("lwdgpchwic");
	passwords[4] = strdup("rdtgzvw");
	passwords[5] = strdup("sduh");
#endif

	passwords = (char **)malloc(10 * sizeof(char*));
	if (!passwords) {
		rv = EXIT_FAILURE; goto finish;
	}
	passwords[0] = strdup("a");
	passwords[1] = strdup("aa");
	passwords[2] = strdup("aaa");
	passwords[3] = strdup("aaaa");
	passwords[4] = strdup("aaaaa");
	passwords[5] = strdup("aaaaaa");
	passwords[6] = strdup("aaaaaaa");
	passwords[7] = strdup("aaaaaaaa");
	passwords[8] = strdup("aaaaaaaaa");
	passwords[9] = strdup("aaaaaaaaaa");

	assert(passwordCracker(10, passwords, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
	printf("%s\n", buf);

finish:
	return rv;
}
