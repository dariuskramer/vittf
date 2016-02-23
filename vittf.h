#ifndef VITTF_H
#define VITTF_H

#include <stdio.h>
#include <string.h>

#define v_assert(expression) \
	do { \
		if (!(expression)) {\
			printf("Failed:\tFILE(%s), LINE(%d), Expression(%s)\n", __FILE__, __LINE__, #expression); \
			exit(1); \
		} \
	} while (0)

#define v_assert_str(expected, actual) \
	do { \
		if (strcmp((expected), (actual)) != 0) {\
			printf("Failed:\tFILE(%s), LINE(%d), Expression(%s != %s)", __FILE__, __LINE__, (expected), (actual)); \
			exit(1);\
		}\
	} while (0)

#define v_test_success(name) printf("%s ✓\n", (name))
#define v_suite_success printf("\n\n=========\nFULL TEST ✓\n")

#endif
