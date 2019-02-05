#include <stddef.h>
#include "../../string-helpers.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include "test.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  return 0;
}

/* The test initialization function.
 * Opens the temporary file used by the test.
 */
void init_test1(void) {
  return;
}

/* The test cleanup function.
 * Closes the temporary file used by the test in particular.
 */
void clean_test1(void) {
  return;
}

/* Simple test of is_digit().
 */
void testISDIGIT_Integers(void) {
  CU_ASSERT_FALSE(is_digit(0));
  CU_ASSERT_FALSE(is_digit(9));
  CU_ASSERT_FALSE(is_digit(-1));
}

void testISDIGIT_Digits(void) {
  CU_ASSERT_TRUE(is_digit('1'));
  CU_ASSERT_TRUE(is_digit('0'));
  CU_ASSERT_TRUE(is_digit('9'));
}

void testISDIGIT_EscChars(void) {
  CU_ASSERT_FALSE(is_digit('\0'));
  CU_ASSERT_FALSE(is_digit('\"'));
  CU_ASSERT_FALSE(is_digit('\n'));
}

void testISALPHA_Str(void) {
    CU_ASSERT_FALSE(is_alpha(4));
    CU_ASSERT_FALSE(is_alpha(5));
    CU_ASSERT_FALSE(is_alpha(6));
}

void testISALPHA_Integer(void) {
    CU_ASSERT_FALSE(is_alpha(1));
    CU_ASSERT_FALSE(is_alpha(2));
    CU_ASSERT_FALSE(is_alpha(3));
}

void testISALPHA_Alpha(void) {
    CU_ASSERT_TRUE(is_alpha('a'));
    CU_ASSERT_TRUE(is_alpha('b'));
    CU_ASSERT_TRUE(is_alpha('c'));
}

void testISSPACE_Space(void) {
    CU_ASSERT_TRUE(is_space(' '));
}

void testISSPACE_Digit(void) {
    CU_ASSERT_FALSE(is_space('2'));
}

void testISSPACE_Str(void) {
    CU_ASSERT_FALSE(is_space('$'));
}

void testISIDENTIFIERCOMPONENT_Space(void) {
    CU_ASSERT_FALSE(is_identifier_component(' '));
}

void testISIDENTIFIERCOMPONENT_Identifier(void) {
    CU_ASSERT_TRUE(is_identifier_component('a'));
}

void testISIDENTIFIERCOMPONENT_Symbol(void) {
    CU_ASSERT_FALSE(is_identifier_component('&'));
}

void testISVALIDIDENTIFIER_Str(void) {
    CU_ASSERT_FALSE(is_valid_identifier('&'));
}

void testISVALIDIDENTIFIER_Not(void) {
    CU_ASSERT_TRUE(is_valid_identifier("abc"));
}

void testISVALIDIDENTIFIER_False(void) {
    CU_ASSERT_FALSE(is_valid_identifier('@'));
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_TestInfo isdigit_tests[] = {{"Test actual digits", testISDIGIT_Digits},
                                 {"Test esc chars", testISDIGIT_EscChars},
                                 {"Test numbers", testISDIGIT_Integers},
                                 CU_TEST_INFO_NULL};

  CU_SuiteInfo suites[] = {{"is_digit testing", init_suite1, clean_suite1,
                           isdigit_tests},
                           CU_SUITE_INFO_NULL};

  CU_TestInfo isalpha_tests[] = {{"Test actual alpha", testISALPHA_Alpha},
                                   {"Test alpha", testISALPHA_Integer},
                                   {"Test alpha", testISALPHA_Str},
                                   CU_TEST_INFO_NULL};

  CU_SuiteInfo isalpha_suites[] = {{"is_alpha testing", init_suite1, clean_suite1,
                             isalpha_tests},
                             CU_SUITE_INFO_NULL};

  CU_TestInfo isspace_tests[] = {{"Test actual space", testISSPACE_Digit},
                                   {"Test space", testISSPACE_Space},
                                   {"Test space", testISSPACE_Str},
                                   CU_TEST_INFO_NULL};

  CU_SuiteInfo isspace_suites[] = {{"is_space testing", init_suite1, clean_suite1,
                             isspace_tests},
                             CU_SUITE_INFO_NULL};

  CU_TestInfo isidentifiercomponent_tests[] = {{"Test actual identifiercomponent", testISIDENTIFIERCOMPONENT_Identifier},
                                     {"Test identifiercomponent", testISIDENTIFIERCOMPONENT_Space},
                                     {"Test identifiercomponent", testISIDENTIFIERCOMPONENT_Symbol},
                                     CU_TEST_INFO_NULL};

  CU_SuiteInfo isvalididentifier_suites[] = {{"is_identifiercomponent testing", init_suite1, clean_suite1,
                               isidentifiercomponent_tests},
                               CU_SUITE_INFO_NULL};

  CU_TestInfo isvalididentifier_tests[] = {{"Test actual valididentifier", testISVALIDIDENTIFIER_False},
                                       {"Test valididentifier", testISVALIDIDENTIFIER_Not},
                                       {"Test valididentifier", testISVALIDIDENTIFIER_Str},
                                       CU_TEST_INFO_NULL};

  CU_SuiteInfo isvalididentifier_suites[] = {{"is_valididentifier testing", init_suite1, clean_suite1,
                                 isvalididentifier_tests},
                                 CU_SUITE_INFO_NULL};
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  if (CU_register_suites(suites)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
