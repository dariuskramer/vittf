#ifndef VITTF_H
#define VITTF_H

#include <stdio.h>
#include <string.h>

#define v_assert(expression) \
	if (!(expression)) {\
		printf("Failed:\tFILE(%s), LINE(%d), Expression(%s)\n", __FILE__, __LINE__, #expression);}

#define v_assert_str(expected, actual) \
	if (strcmp((expected), (actual)) != 0) {\
		printf("Failed:\tFILE(%s), LINE(%d), Expression(%s != %s)", __FILE__, __LINE__, (expected), (actual));}

#endif
