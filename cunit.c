//
// Created by Guillaume LAROYENNE on 19/03/18.
//

#include <zconf.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include "vector.h"

#define SIZE_MAX 500

static void **functionArray = NULL;
static char **nameArray = NULL;
static int arrayLen = 0;
static char assertName[SIZE_MAX];


void printErrorValue(const char *message, const char *actual, const char *excepted) {
    sprintf(assertName, "%s\nExpected :%s\nActual :%s\n", message, actual, excepted);
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


void cunit_assert(bool b) {

    if (!b) {
        if (strlen(assertName) != 0) {
            fprintf(stderr, "%s\n", assertName);
        }

        exit(EXIT_FAILURE);
    }
}


void cunit_assert_true(bool b) {

    printErrorValue("Assert true", "false", "true");
    cunit_assert(b);
}


void cunit_assert_fase(bool b) {

    printErrorValue("Assert false", "true", "false");
    cunit_assert(!b);
}

void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *)) {

    char elt1str[100];
    char elt2str[100];

    sprintf(elt1str, "%p", elt1);
    sprintf(elt2str, "%p", elt2);

    printErrorValue("Assert equals", elt1str, elt2str);
    cunit_assert(pFunction(elt1, elt2));
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
            printf("[TEST %d %s : failed]\n", i, nameArray[i]);
        } else {
            printf("[TEST %d %s : success]\n", i, nameArray[i]);
        }
    }


    if (arrayLen > 0) {
        free(functionArray);
        for (int i = 0; i < arrayLen; ++i) {
            free(nameArray);
        }
        arrayLen = 0;
    }
}


