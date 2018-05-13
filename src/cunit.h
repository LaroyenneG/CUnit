/*
 * Created by Guillaume LAROYENNE on 19/03/18.
 */

#ifndef CUNIT_H
#define CUNIT_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * Assert equals functions
 */

#define ASSERT_TRUE(b) cunit_assert_true(b, __FILE__, __LINE__)

#define ASSERT_FALSE(b) cunit_assert_false(b, __FILE__, __LINE__)

#define ASSERT_EQUALS_INTEGER(e, a) cunit_assert_equals_integer(e, a,  __FILE__, __LINE__)

#define ASSERT_EQUALS_POINTER(e, a) cunit_assert_equals_pointer(e, a, __FILE__, __LINE__)

#define ASSERT_EQUALS(e1, e2, func) cunit_assert_equals(e1, e2, func, __FILE__, __LINE__)

#define ASSERT_EQUALS_STRING(e, a) cunit_assert_equals_string(e, a, __FILE__, __LINE__)

#define ASSERT_NULL(p) cunit_assert_null(p,  __FILE__, __LINE__)

#define ASSERT_EQUALS_REAL(e, a) cunit_assert_equals_real(e, a, __FILE__, __LINE__)


/**
 * Assert not equals functions
 */

#define ASSERT_NOT_EQUALS_INTEGER(e, a) cunit_assert_not_equals_integer(e, a,  __FILE__, __LINE__)

#define ASSERT_NOT_EQUALS(e1, e2, func) cunit_assert_not_equals(e1, e2, func, __FILE__, __LINE__)

#define ASSERT_NOT_EQUALS_POINTER(e, a) cunit_assert_not_equals_pointer(e, a, __FILE__, __LINE__)

#define ASSERT_NOT_EQUALS_REAL(e, a) cunit_assert_not_equals_real(e, a, __FILE__, __LINE__)

#define ASSERT_NOT_NULL(p) cunit_assert_not_null(p,   __FILE__, __LINE__)

#define ASSERT_NOT_EQUALS_STRING(e, a) cunit_assert_not_equals_string(e, a, __FILE__, __LINE__)


/**
 * Tools functions
 */

#define ASSERT_FAIL() cunit_assert_fail( __FILE__, __LINE__)

#define CUNIT_ADD_TEST_FUNCTION(func, name) cunit_add_function(func, name)

#define CUNIT_RUN() cunit_exec_test()


#ifdef __cplusplus
extern "C" {
#endif

extern void cunit_assert_true(bool b, const char *file, int line);

extern void cunit_assert_false(bool b, const char *file, int line);

extern void cunit_assert_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line);

extern void
cunit_assert_not_equals(void *elt1, void *elt2, bool(*pFunction)(void *, void *), const char *file, int line);

extern void cunit_assert_equals_integer(long long int expected, long long int actual, const char *file, int line);

extern void cunit_assert_not_equals_integer(long long int expected, long long int actual, const char *file, int line);

extern void cunit_assert_not_equals_string(const char *expected, const char *actual, const char *file, int line);

extern void cunit_assert_equals_string(const char *expected, const char *actual, const char *file, int line);

extern void cunit_assert_equals_pointer(void *expected, void *actual, const char *file, int line);

extern void cunit_assert_null(void *pVoid, const char *file, int line);

extern void cunit_assert_not_null(void *pVoid, const char *file, int line);

extern void cunit_assert_equals_real(long double expected, long double actual, const char *file, int line);

extern void cunit_assert_not_equals_real(long double expected, long double actual, const char *file, int line);

extern void cunit_assert_fail(const char *file, int line);

extern void cunit_add_function(void(*function)(void), const char *name);

extern void cunit_exec_test();

#ifdef __cplusplus
}
#endif

#endif
