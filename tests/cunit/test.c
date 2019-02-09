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
    CU_ASSERT_TRUE(is_alpha('a'));
    CU_ASSERT_TRUE(is_alpha('d'));
    CU_ASSERT_TRUE(is_alpha('z'));
}

void testISALPHA_Integer(void) {
    CU_ASSERT_FALSE(is_alpha(1));
    CU_ASSERT_FALSE(is_alpha(2));
    CU_ASSERT_FALSE(is_alpha(3));
}

void testISALPHA_Alpha(void) {
    CU_ASSERT_FALSE(is_alpha(' '));
    CU_ASSERT_FALSE(is_alpha(' '));
    CU_ASSERT_FALSE(is_alpha(' '));
}

void testISSPACE_Space(void) {
    CU_ASSERT_TRUE(is_space(' '));
    CU_ASSERT_TRUE(is_space(' '));
    CU_ASSERT_TRUE(is_space(' '));
}

void testISSPACE_Digit(void) {
    CU_ASSERT_FALSE(is_space('2'));
    CU_ASSERT_FALSE(is_space('3'));
    CU_ASSERT_FALSE(is_space('4'));
}

void testISSPACE_Str(void) {
    CU_ASSERT_FALSE(is_space('$'));
    CU_ASSERT_FALSE(is_space('('));
    CU_ASSERT_FALSE(is_space(')'));
}

void testISIDENTIFIERCOMPONENT_Space(void) {
    CU_ASSERT_FALSE(is_identifier_component(' '));
    CU_ASSERT_FALSE(is_identifier_component('*'));
    CU_ASSERT_FALSE(is_identifier_component('^'));
}

void testISIDENTIFIERCOMPONENT_Identifier(void) {
    CU_ASSERT_TRUE(is_identifier_component('a'));
    CU_ASSERT_TRUE(is_identifier_component('1'));
    CU_ASSERT_TRUE(is_identifier_component('_'));
}

void testISIDENTIFIERCOMPONENT_Symbol(void) {
    CU_ASSERT_FALSE(is_identifier_component('&'));
    CU_ASSERT_FALSE(is_identifier_component(' '));
    CU_ASSERT_FALSE(is_identifier_component('('));
}

void testISVALIDIDENTIFIER_Str(void) {
    CU_ASSERT_FALSE(is_valid_identifier("&"));
    CU_ASSERT_FALSE(is_valid_identifier("*"));
    CU_ASSERT_FALSE(is_valid_identifier("^"));
}

void testISVALIDIDENTIFIER_Not(void) {
    CU_ASSERT_TRUE(is_valid_identifier("abc"));
    CU_ASSERT_TRUE(is_valid_identifier("a90"));
    CU_ASSERT_TRUE(is_valid_identifier("z_8"));
}

void testISVALIDIDENTIFIER_False(void) {
    CU_ASSERT_FALSE(is_valid_identifier("1"));
    CU_ASSERT_FALSE(is_valid_identifier(" "));
    CU_ASSERT_FALSE(is_valid_identifier("4"));
}


void testStrConcat1(void) {
    char* output = "I hate and want to drop 61c";
    char* strings[5] = {"I hate ", "and", "want", "to drop", "61c"};
    CU_ASSERT_STRING_EQUAL(str_concat(strings, 5), output);
}

void testStrConcat2(void) {
    char* output = "I am myself";
    char* strings[3] = {"I ", "am ", "myself"};
    CU_ASSERT_STRING_EQUAL(str_concat(strings, 3), output);
}

void testStrConcat3(void) {
    char* output = "I love russell westbrook";
    char* strings[4] = {"I ", "love ", "russell ","westbrook"};
    CU_ASSERT_STRING_EQUAL(str_concat(strings, 4), output);
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
  CU_TestInfo isalpha_tests[] = {{"Test actual alpha", testISALPHA_Alpha},
                                 {"Test alphahj", testISALPHA_Integer},
                                 {"Test alpha", testISALPHA_Str},
                                 CU_TEST_INFO_NULL};

  CU_TestInfo isspace_tests[] = {{"Test actual space", testISSPACE_Digit},
                                 {"Test spacejh", testISSPACE_Space},
                                 {"Test space", testISSPACE_Str},
                                 CU_TEST_INFO_NULL};

  CU_TestInfo isidentifiercomponent_tests[] = {{"Test actual identifiercomponent", testISIDENTIFIERCOMPONENT_Identifier},
                                     {"Test identifiercomponentiugu", testISIDENTIFIERCOMPONENT_Space},
                                     {"Test identifiercomponent", testISIDENTIFIERCOMPONENT_Symbol},
                                     CU_TEST_INFO_NULL};

  CU_TestInfo isvalididentifier_tests[] = {{"Test actual valididentifier", testISVALIDIDENTIFIER_False},
                                       {"Test valididentifierjhg", testISVALIDIDENTIFIER_Not},
                                       {"Test valididentifier", testISVALIDIDENTIFIER_Str},
                                       CU_TEST_INFO_NULL};

  CU_TestInfo isstrconcat_tests[] = {{"Test actual a", testStrConcat1},
                                       {"Test b", testStrConcat2},
                                       {"Test c", testStrConcat3},
                                          CU_TEST_INFO_NULL};
  CU_SuiteInfo suites[] = {{"is_digit testing", init_suite1, clean_suite1,
                           isdigit_tests}, {"is_alpha testing", init_suite1, clean_suite1, isalpha_tests}, {"is_space testing", init_suite1, clean_suite1, isspace_tests}, {"is_identifiercomponent testing", init_suite1, clean_suite1, isidentifiercomponent_tests}, {"is_valididentifier testing", init_suite1, clean_suite1, isvalididentifier_tests}, {"strconcat", init_suite1, clean_suite1, isstrconcat_tests}, CU_SUITE_INFO_NULL};


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
