#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include "../src/vm.h"

#define TOLERANCE 0.00001


void setup(void)
{
    initVM();
}

void teardown(void)
{
}

START_TEST(test_money_create)
{

    Chunk c;
    initChunk(&c);
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
    freeChunk(&c);
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
    tcase_add_test(tc_core, test_money_create);
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
