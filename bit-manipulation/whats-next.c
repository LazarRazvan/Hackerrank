/**
 * https://www.hackerrank.com/challenges/whats-next/problem
 * Copyright (C) 2024 Lazar Razvan.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*****************************************************************************/
 
 /**
  * Main idea: Identify the least significant sequence of '01' bits and switch
  * them to maintain the total number of set bits, thereby generating the next
  * larger number.
  *
  * For an array with an even number of elements, there will always be trailing
  * 0 bits. To find the smallest number greater than B while preserving the
  * number of set bits:
  * 1. Locate and switch the first occurrence of the '01' bit sequence.
  * 2. Move 1 bits to the end of the sequence.
  * 3. Bring the trailing zeros before the remaining bits.
 */


/*****************************************************************************/

/**
 * TODO:
 *
 * The following functions have to be updated in order long array values to be
 * supported.
 */
long parse_long(char* str) {
	char* endptr;
	long value = strtol(str, &endptr, 10);

	if (endptr == str || *endptr != '\0') {
		exit(EXIT_FAILURE);
	}

	return value;
}

#if 0
int main()
{
	int t = parse_int(ltrim(rtrim(readline())));

	for (int t_itr = 0; t_itr < t; t_itr++) {
		int arr_count = parse_int(ltrim(rtrim(readline())));

		char** arr_temp = split_string(rtrim(readline()));

		long* arr = malloc(arr_count * sizeof(long));

		for (int i = 0; i < arr_count; i++) {
			long arr_item = parse_long(*(arr_temp + i));

			*(arr + i) = arr_item;
		}

		whatsNext(arr_count, arr);
	}

	return 0;
}
#endif


/*****************************************************************************/


static void __base_print(int new_count, int end, long *arr)
{
	printf("%d\n", new_count);

	for (int i = 0; i < end; i++)
		printf("%ld ", arr[i]);
}

static void __even_elements(int arr_count, long *arr)
{
	int last_1s, last_0s;

	/****************************************************************
	 * By knowing that the array have an even number of elements, it
	 * is certainly that we have trailing 0 bits.
	 ***************************************************************/
	last_1s = arr_count - 2;
	last_0s = last_1s - 1;

	/****************************************************************
	 * Case 1 (...111100011100 -> ...111100101100 -> ...111100100011)
	 *
	 * Multiple 0 and 1 bits.
	 ***************************************************************/
	if (arr[last_0s] != 1 && arr[last_1s] != 1) {
		__base_print(arr_count + 1, last_0s, arr);
		printf("%ld 1 %ld %ld\n", arr[last_0s] - 1, arr[arr_count - 1] + 1,
				arr[last_1s] - 1);

		goto finish;
	}
	
	/****************************************************************
	 * Case 2 (...1111000100 -> ...1111001000)
	 *
	 * Multiple 0 bits and single 1 bit.
	 ***************************************************************/
	if (arr[last_0s] != 1 && arr[last_1s] == 1) {
		__base_print(arr_count, last_0s, arr);
		printf("%ld 1 %ld\n", arr[last_0s] - 1, arr[arr_count - 1] + 1);

		goto finish;
	}

	/****************************************************************
	 * Case 3 (...11110111000 -> ...11111011000 -> ...11111000011)
	 *
	 * Single 0 bit and multiple 1 bits.
	 ***************************************************************/
	if (arr[last_0s] == 1 && arr[last_1s] != 1) {
		__base_print(arr_count - 1, last_0s - 1, arr);
		printf("%ld %ld %ld\n", arr[last_0s - 1] + 1, arr[arr_count - 1] + 1,
				arr[last_1s] - 1);

		goto finish;
	}

	/****************************************************************
	 * Case 4 (...111101000 -> ...111110000)
	 *
	 * Single 0 bit and single 1 bit.
	 ***************************************************************/
	if (arr[last_0s] == 1 && arr[last_1s] == 1) {
		__base_print(arr_count - 2, last_0s - 1, arr);
		printf("%ld %ld\n", arr[last_0s - 1] + 1, arr[arr_count - 1] + 1);

		goto finish;
	}

finish:
	return;
}

static void __odd_elements(int arr_count, long *arr)
{
	int last_1s, last_0s;

	/****************************************************************
	 * By knowing that the array have an odd number of elements, it
	 * is certainly that we have trailing 1 bits.
	 ***************************************************************/
	last_1s = arr_count - 1;
	last_0s = last_1s - 1;

	/****************************************************************
	 * Case 1 (...1111000111 -> ...1111001011)
	 *
	 * Multiple 0 and 1 bits.
	 ***************************************************************/
	if (arr[last_0s] != 1 && arr[last_1s] != 1) {
		__base_print(arr_count + 2, last_0s, arr);
		printf("%ld 1 1 %ld\n", arr[last_0s] - 1, arr[last_1s] - 1);

		goto finish;
	}
	
	/****************************************************************
	 * Case 2 (...11110001 -> ...11110010)
	 *
	 * Multiple 0 bits and single 1 bit.
	 ***************************************************************/
	if (arr[last_0s] != 1 && arr[last_1s] == 1) {
		__base_print(arr_count + 1, last_0s, arr);
		printf("%ld 1 1\n", arr[last_0s] - 1);

		goto finish;
	}

	/****************************************************************
	 * Case 3 (...11110111 -> ...11111011)
	 *
	 * Single 0 bit and multiple 1 bits.
	 ***************************************************************/
	if (arr[last_0s] == 1 && arr[last_1s] != 1) {
		__base_print(arr_count, last_0s - 1, arr);
		printf("%ld 1 %ld\n", arr[last_0s - 1] + 1, arr[last_1s] - 1);

		goto finish;
	}

	/****************************************************************
	 * Case 4 (...111101 -> ...111110)
	 *
	 * Single 0 bit and single 1 bit.
	 ***************************************************************/
	if (arr[last_0s] == 1 && arr[last_1s] == 1) {
		__base_print(arr_count - 1, last_0s - 1, arr);
		printf("%ld 1\n", arr[last_0s - 1] + 1);

		goto finish;
	}

finish:
	return;
}

void whatsNext(int arr_count, long* arr)
{

	/****************************************************************
	 * Case 1 (1111 -> 10111) / (1 -> 10)
	 ***************************************************************/
	if (arr_count == 1) {
		if (arr[0] == 1)
			printf("2\n1 1\n");
		else
			printf("3\n1 1 %ld\n", arr[0] - 1);
		goto finish;
	}

	/****************************************************************
	 * Case 2
	 * 1. 10   -> 100
	 * 2. 100  -> 1000
	 * 3. 110  -> 1001
	 * 4. 1100 -> 10001
	 ***************************************************************/
	if (arr_count == 2) {
		// 1
		if (arr[0] == 1 && arr[1] == 1) {
			printf("2\n1 2\n");
			goto finish;
		}

		// 2
		if (arr[0] == 1 && arr[1] != 1) {
			printf("2\n1 %ld\n", arr[1] + 1);
			goto finish;
		}

		// 3, 4
		printf("3\n1 %ld %ld\n", arr[1] + 1, arr[0] - 1);
		goto finish;
	}

	//
	if (arr_count % 2)
		__odd_elements(arr_count, arr);
	else
		__even_elements(arr_count, arr);

finish:
	return;
}

int main()
{
	return 0;
}
