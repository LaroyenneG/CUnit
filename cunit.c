//
// Created by Guillaume LAROYENNE on 19/03/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#include <zconf.h>

#define SIZE_MAX 1000
#define STATUS_TEST_MESSAGE "[TEST N°%d %s : %s]\n"

static void **functionArray = NULL;
static char **nameArray = NULL;
static int arrayLen = 0;
static char assertName[SIZE_MAX];


static void cunit_assert_error_equals(const char *message, const char *expected, const char *actual, const char *file,
                                      int line);

static void cunit_assert_error_not_equals(const char *message, const char *actual, const char *file,
                                          int line);

static void cunit_assert_error_null(const char *message, const char *actual, const char *file, int line);

static void cunit_assert_error_not_null(const char *message, const char *file, int line);

static void cunit_assert_error_fail(const char *message, const char *file, int line);

static void cunit_exit(const char *file, int line);


/*
 * Equals functions
 */


void cunit_assert_true(bool b, const char *file, int line) {

    if (!b) {
        cunit_assert_error_equals("Assertion Failure", "false", "true", file, line);
    }
}


void cunit_assert_false(bool b, const char *file, int line) {

    if (b) {
        cunit_assert_error_equals("Assertion Failure", "false", "true", file, line);
    }
}


void cunit_assert_null(void *pVoid, const char *file, int line) {


    char strPointer[20];
    sprintf("%p", pVoid);

    if (pVoid != NULL) {
        cunit_assert_error_null("Assertion Failure", strPointer, file, line);
    }
}

void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line) {

    if (elt1 != elt2 && !pFunction(elt1, elt2)) {
        cunit_assert_error_equals("Comparison Failure", "false", "true", file, line);
    }
}


void cunit_assert_equals_integer(long expected, long actual, const char *file, int line) {

    char srtExpected[20];
    char strActual[20];

    sprintf(srtExpected, "%li", expected);
    sprintf(strActual, "%li", actual);

    if (expected != actual) {
        cunit_assert_error_equals("Assertion Error", srtExpected, strActual, file, line);
    }
}


void cunit_assert_equals_string(const char *expected, const char *actual, const char *file, int line) {

    if (strcmp(expected, actual) != 0) {
        cunit_assert_error_equals("Assertion Error", expected, actual, file, line);
    }
}


void cunit_assert_equals_real(double expected, double actual, const char *file, int line) {

    char srtExpected[20];
    char strActual[20];

    sprintf(srtExpected, "%lf", expected);
    sprintf(strActual, "%lf", actual);


    if (expected != actual) {
        cunit_assert_error_equals("Assertion Error", srtExpected, strActual, file, line);
    }
}


/*
 * Not equals functions
 */

void cunit_assert_not_equals_integer(long expected, long actual, const char *file, int line) {


    char strActual[20];

    sprintf(strActual, "%li", actual);

    if (expected != actual) {
        cunit_assert_error_not_equals("Assertion Error", strActual, file, line);
    }
}


void cunit_assert_not_equals_string(const char *expected, const char *actual, const char *file, int line) {

    if (strcmp(expected, actual) == 0) {
        cunit_assert_error_not_equals("Assertion Error", actual, file, line);
    }
}


void cunit_assert_not_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line) {

    if (elt1 == elt2 || pFunction(elt1, elt2)) {
        cunit_assert_error_equals("Comparison Failure", "true", "false", file, line);
    }
}


void cunit_assert_not_null(void *pVoid, const char *file, int line) {

    if (pVoid == NULL) {
        cunit_assert_error_not_null("Assertion Error", file, line);
    }
}


void cunit_assert_not_equals_real(double expected, double actual, const char *file, int line) {

    char strActual[20];

    sprintf(strActual, "%lf", actual);

    if (expected == actual) {
        cunit_assert_error_not_equals("Assertion Error", strActual, file, line);
    }
}


/*
 * Other test functions
 */

void cunit_assert_fail(const char *file, int line) {

    cunit_assert_error_fail("Assertion Error", file, line);
}


/*
 * Execution functions
 */


void cunit_exec_test() {


    int testsCont[] = {0, 0, 0};

    memset(assertName, '\0', SIZE_MAX);

    void (*function)(void);

    for (int i = 0; i < arrayLen; ++i) {

        function = functionArray[i];

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork()");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            function();
            exit(EXIT_SUCCESS);
        }

        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid()");
            exit(EXIT_FAILURE);
        }


        switch (WEXITSTATUS(status)) {

            case EXIT_FAILURE:
                printf(STATUS_TEST_MESSAGE, i + 1, nameArray[i], "failed");
                testsCont[1]++;
                break;

            case EXIT_SUCCESS:
                printf(STATUS_TEST_MESSAGE, i + 1, nameArray[i], "success");
                testsCont[2]++;
                break;

            default:
                printf(STATUS_TEST_MESSAGE, i + 1, nameArray[i], "status");
                break;

        }

        testsCont[0]++;
    }


    if (arrayLen > 0) {
        free(functionArray);
        for (int i = 0; i < arrayLen; ++i) {
            free(nameArray[i]);
        }
        free(nameArray);
        arrayLen = 0;
    }

    char resultMessage[500];

    sprintf(resultMessage, "\nCUnit result :\n");
    for (int j = 0; j < sizeof(testsCont) / sizeof(int); ++j) {

        switch (j) {

            case 0:
                sprintf(resultMessage, "\x1B[34m");
                break;

            case 1:
                sprintf(resultMessage, "\x1B[31m");
                break;

            case 2:
                sprintf(resultMessage, "\x1B[32m");
                break;

            default:
                exit(EXIT_FAILURE);
        }

        sprintf(resultMessage, "\t\t\t\t%d ", testsCont[j]);

        if (testsCont[j] < 1) {
            sprintf(resultMessage, "test");
        } else {
            sprintf(resultMessage, "tests");
        }

        sprintf(resultMessage, " ");

        switch (j) {

            case 0:
                sprintf(resultMessage, "done");
                break;

            case 1:
                sprintf(resultMessage, "failed");
                break;

            case 2:
                sprintf(resultMessage, "passed");
                break;

            default:
                exit(EXIT_FAILURE);
        }

        sprintf(resultMessage, "\x1B[0m\n");

        printf("%s", resultMessage);

        fflush(stdout);
    }


}


void cunit_add_function(void(*function)(void), const char *name) {


    if (arrayLen == 0) {
        functionArray = malloc(sizeof(void *));
        nameArray = malloc(sizeof(char *));
        if (functionArray == NULL || nameArray == NULL) {
            perror("realloc()");
            exit(EXIT_FAILURE);
        }

    } else {
        functionArray = realloc(functionArray, sizeof(void *) * (arrayLen + 1));
        nameArray = realloc(nameArray, sizeof(char *) * (arrayLen + 1));
        if (functionArray == NULL || nameArray == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
    }

    functionArray[arrayLen] = function;

    nameArray[arrayLen] = malloc(sizeof(char) * (strlen(name)) + 1);
    if (nameArray[arrayLen] == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    strcpy(nameArray[arrayLen], name);
    arrayLen++;
}


/*
 * static functions
 */

void cunit_assert_error_equals(const char *message, const char *expected, const char *actual, const char *file,
                               int line) {

    fprintf(stderr, "%s\n\tExepected\t: %s\n\tActual\t\t: %s\n", message, expected, actual);
    cunit_exit(file, line);
}


void cunit_assert_error_not_equals(const char *message, const char *actual, const char *file,
                                   int line) {

    fprintf(stderr, "%s\nValues should be different.\tActual : %s\n", message, actual);
    cunit_exit(file, line);
}


void cunit_assert_error_null(const char *message, const char *actual, const char *file, int line) {

    fprintf(stderr, "%s\nExpected null, but was:<%s>\n", message, actual);
    cunit_exit(file, line);
}

void cunit_assert_error_not_null(const char *message, const char *file, int line) {

    fprintf(stderr, "%s\n", message);
    cunit_exit(file, line);
}

void cunit_assert_error_fail(const char *message, const char *file, int line) {

    fprintf(stderr, "%s\n", message);
    cunit_exit(file, line);
}


void cunit_exit(const char *file, int line) {

    fprintf(stderr, "at %s:%d\n", file, line);
    exit(EXIT_FAILURE);
}