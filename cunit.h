//
// Created by Guillaume LAROYENNE on 19/03/18.
//

#ifndef CUNIT_H
#define CUNIT_H

#include <stdbool.h>

#define ASSERT_TRUE(b) cunit_assert_true(b, __FILE__, __LINE__);

#define ASSERT_FALSE(b) cunit_assert_false(b, __FILE__, __LINE__);

#define ASSERT_EQUALS(e1, e2, func) cunit_assert_equals(e1, e2, func, __FILE__, __LINE__);

#define ASSERT_NOT_EQUALS(e1, e2, func) cunit_assert_not_equals(e1, e2, func, __FILE__, __LINE__);

#define CUNIT_ADD_TEST_FUNCTION(func, name) cunit_add_function(func, name);

#define CUNIT_RUN() cunit_exec_test();

#ifdef __cplusplus
extern "C" {
#endif

extern void cunit_assert_true(bool b, const char *file, int line);

extern void cunit_assert_false(bool b, const char *file, int line);

extern void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line);

extern void
cunit_assert_not_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line);

extern void cunit_exec_test();

extern void cunit_add_function(void(*function)(void), const char *name);

#ifdef __cplusplus
}
#endif


#endif //CUNIT_H
