#include <algo.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_push() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_push_multiple() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_push_over() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_pop() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_pop_empty() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_pop_multiple() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_at_initial() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_at_out_of_range() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_at_after_loop() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_is_empty() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

void test_is_empty_full() {
    TEST_FAIL_MESSAGE("TEST NOT IMPLEMENTED");
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_push);
    RUN_TEST(test_push_multiple);
    RUN_TEST(test_push_over);

    RUN_TEST(test_pop);
    RUN_TEST(test_pop_empty);
    RUN_TEST(test_pop_multiple);

    RUN_TEST(test_at_initial);
    RUN_TEST(test_at_out_of_range);
    RUN_TEST(test_at_after_loop);

    RUN_TEST(test_is_empty);
    RUN_TEST(test_is_empty_full);

    UNITY_END();
}