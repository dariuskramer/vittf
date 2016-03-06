#ifndef VITTF_H
#define VITTF_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define v_assert(expression) \
	do { \
		if (!(expression)) {\
			printf("\x1b[41mFailed >>>\x1b[0m FILE(%s), LINE(%d), Expression(%s)\n", __FILE__, __LINE__, #expression); \
			exit(1); \
		} \
	} while (0)

#define v_assert_str(expected, actual) \
	do { \
		if (strcmp((expected), (actual)) != 0) {\
			printf("\x1b[41mFailed>\x1b[0m\tFILE(%s), LINE(%d), Expression(%s != %s)", __FILE__, __LINE__, (expected), (actual)); \
			exit(1);\
		}\
	} while (0)

#define v_assert_pass(expression) \
	do { \
		if (!(expression)) {\
			printf("\x1b[41mFailed >>>\x1b[0m FILE(%s), LINE(%d), Expression(%s)\n", __FILE__, __LINE__, #expression); \
		} \
	} while (0)

#define v_assert_pass_str(expected, actual) \
	do { \
		if (strcmp((expected), (actual)) != 0) {\
			printf("\x1b[41mFailed>\x1b[0m\tFILE(%s), LINE(%d), Expression(%s != %s)", __FILE__, __LINE__, (expected), (actual)); \
		}\
	} while (0)

#define v_test_success(name) \
	(printf("%s ✓\n", (name)))
#define v_suite_success(suite) \
	(printf("---> Suite %s ✓\n\n", (suite)))
#define v_full_success(test) \
	(printf("=========\n\x1b[32mFULL TEST FOR %s ✓\x1b[0m\n", (test)))

/*
 * Stdout Redirection
 *
 * - Créer une référence supplémentaire vers le FILE de stdout
 *		Les objets pointés par les référence ne sont pas distinguable
 *
 * [0] => connect to the read end of the pipe (output)
 * [1] => connect to the write end of the pipe (input)
 * Les données écrite dans [1] peuvent etre lues dans [0]
 * Le pipe est actif tant que les 2 fds ne sont pas clos
 *
 * Le fd 1 étant déjà occupé, dup2() le clos.
 * Ensuite dup2() duplique la référence vers l'input du pipe en utilisant
 * le second parametre envoyé, a savoir 1
 */
static int	v_stdout_ref;
static int	v_pipe_redirect[2];
static int	v_read_return;

#define V_REDIRECT_STDOUT_SETUP \
	do { \
		setvbuf(stdout, NULL, _IONBF, BUFSIZ); \
		v_stdout_ref = dup(1); \
		if ((pipe(v_pipe_redirect)) == -1) {\
			fprintf(stderr, "Pipe() error !\n"); \
			exit(10); \
		}\
		if ((dup2(v_pipe_redirect[1], 1)) == -1) {\
			fprintf(stderr, "Dup2() error !\n"); \
			exit(11); \
		}\
	} while (0)

#define V_REDIRECT_STDOUT_READ(v_buffer, v_buffer_size) \
	do { \
		if ((dup2(v_stdout_ref, 1)) == -1) {\
			fprintf(stderr, "Dup2() error !\n"); \
			exit(13); \
		}\
		v_read_return = read(v_pipe_redirect[0], v_buffer, v_buffer_size); \
		if (v_read_return == -1) {\
			fprintf(stderr, "Read() error !\n"); \
			exit(12); \
		}\
		v_buffer[v_read_return] = '\0';\
	} while (0)

#define V_REDIRECT_STDOUT_TEARDOWN \
	do { \
		if ((dup2(v_stdout_ref, 1)) == -1) {\
			fprintf(stderr, "Dup2() error !\n"); \
			exit(13); \
		}\
		close(v_pipe_redirect[0]); \
		close(v_pipe_redirect[1]); \
		close(v_stdout_ref); \
	} while (0)

#endif
