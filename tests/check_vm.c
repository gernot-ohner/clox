#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include "../src/vm.h"

#define TOLERANCE 0.00001


Chunk c;

void setup(void)
{
    initVM();
    initChunk(&c);
}

void teardown(void)
{
    freeChunk(&c);
}

START_TEST(test_subtraction_and_multiplication) {

    { // set up chunk
        int constant = addConstant(&c, 1.2);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 123);

        constant = addConstant(&c, 3.4);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 125);

        writeChunk(&c, OP_SUBTRACT, 126);

        constant = addConstant(&c, 5.6);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 127);

        writeChunk(&c, OP_MULTIPLY, 128);
        writeChunk(&c, OP_RETURN, 123);
    } // set up chunk

    VM* vm = getVm();
    const Value expected = -12.32;

    // when
    interpretChunk(&c);

    // then
    Value actual = *(vm->stackTop);
    ck_assert_double_eq_tol(actual, expected, TOLERANCE);
}
END_TEST

START_TEST(test_additon_and_division)
{

    { // set up chunk
        int constant = addConstant(&c, 1.2);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 123);

        constant = addConstant(&c, 3.4);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 125);

        writeChunk(&c, OP_ADD, 126);

        constant = addConstant(&c, 5.6);
        writeChunk(&c, OP_CONSTANT, 123);
        writeChunk(&c, constant, 127);

        writeChunk(&c, OP_DIVIDE, 128);
        writeChunk(&c, OP_RETURN, 123);
    } // set up chunk
    VM* vm = getVm();
    const Value expected = 0.821429;

    // when
    interpretChunk(&c);

    // then
    Value actual = *(vm->stackTop);
    ck_assert_double_eq_tol(actual, expected, TOLERANCE);

    // finally
}
END_TEST

Suite * vm_suite(void)
{
    Suite *s;
    TCase *tc_core;
//    TCase *tc_limits;

    s = suite_create("Money");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_additon_and_division);
    tcase_add_test(tc_core, test_subtraction_and_multiplication);
    suite_add_tcase(s, tc_core);

    // I left this here for a template of how to add additional test cases
    /* Limits test case */
//    tc_limits = tcase_create("Limits");
//
//    tcase_add_test(tc_limits, test_money_create_neg);
//    tcase_add_test(tc_limits, test_money_create_zero);
//    suite_add_tcase(s, tc_limits);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = vm_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
