#pragma once


// Include all the headers needed for unit tests
//   * signal.h to catch SIGSEGV
//   * check.h is the unit testing library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <check.h>


// Useful macro to convert a bare word to a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


// Test case strings
// Return the input and the output
#define TEST_MSG(in, exp) "Input: " #in ", Expected Result: " #exp
#define TEST_CMP(in, exp, act) "Input: " #in ", Expected: " #exp ", Actual: " #act


/**
 * @brief Create test case and add it to suite
 *
 * @note setup/teardown fixture functions are run before and after each unit
 * test inside the address space of the test
 * @note `TCase *tc = tcase_create("func")`: Creates test case to be added to
 * the suite
 *
 * @param suite Create suite variable in some function and pass it in here
 * @param setup_fixture Setup function
 * @param teardown_fixture Teardown function : NULL if none
 * @param func Name of test being added to the test case
 */
#define tcase_add(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(suite, tc); \
}


/* TEST SUITES */
extern Suite *part1_suite(void);
