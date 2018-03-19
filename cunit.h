//
// Created by Guillaume LAROYENNE on 19/03/18.
//

#ifndef GL_LIBRARY_CUNIT_H
#define GL_LIBRARY_CUNIT_H


#include <stdbool.h>

#define ASSERT_TRUE(b) cunit_assert_true(b);

#define ASSERT_EQUALS(e1, e2, func) void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *));

#define CUNIT_RUN() cunit_exec_test();

extern void cunit_add_function(void(*function)(void), const char *name);

extern void cunit_assert_true(bool b);

extern void cunit_assert_fase(bool b);

extern void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *));

extern void cunit_exec_test();

#endif //GL_LIBRARY_CUNIT_H
