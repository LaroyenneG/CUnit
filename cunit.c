//
// Created by Guillaume LAROYENNE on 19/03/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#include <zconf.h>

#define SIZE_MAX 500

static void **functionArray = NULL;
static char **nameArray = NULL;
static int arrayLen = 0;
static char assertName[SIZE_MAX];


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


void cunit_assert(const char *message, const char *expected, const char *actual, const char *file, int line) {

    fprintf(stderr, "%s\n\tExepected\t: %s\n\tActual\t\t: %s\n", message, expected, actual);
    fprintf(stderr, "at %s:%d\n", file, line);

    exit(EXIT_FAILURE);
}


void cunit_assert_true(bool b, const char *file, int line) {

    if (!b) {
        cunit_assert("Assertion Failure", "false", "true", file, line);
    }
}


void cunit_assert_false(bool b, const char *file, int line) {

    if (b) {
        cunit_assert("Assertion Failure", "false", "true", file, line);
    }
}


void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line) {

    if (!pFunction(elt1, elt2)) {
        cunit_assert("Comparison Failure", "false", "true", file, line);
    }
}


void cunit_assert_not_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line) {

    if (pFunction(elt1, elt2)) {
        cunit_assert("Comparison Failure", "true", "false", file, line);
    }
}


void cunit_exec_test() {

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
        waitpid(pid, &status, 0);

        if (status != EXIT_SUCCESS) {
            fprintf(stderr, "[TEST %d %s : failed]\n", i, nameArray[i]);
        } else {
            fprintf(stdout, "[TEST %d %s : success]\n", i, nameArray[i]);
        }
    }


    if (arrayLen > 0) {
        free(functionArray);
        for (int i = 0; i < arrayLen; ++i) {
            free(nameArray[i]);
        }
        free(nameArray);
        arrayLen = 0;
    }
}




