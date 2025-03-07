#include <algo.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_push() {
    float data[1];
    CircularBuffer buf(data, 1);

    buf.push(0.0);

    TEST_ASSERT_EQUAL_INT(1, buf.count());

    TEST_ASSERT_EQUAL_FLOAT(0.0, buf.at(0));
}

void test_push_multiple() {
    float data[3];
    CircularBuffer buf(data, 3);

    buf.push(0.0);
    buf.push(1.0);
    buf.push(2.0);

    TEST_ASSERT_EQUAL_INT(3, buf.count());

    TEST_ASSERT_EQUAL_FLOAT(0.0, buf.at(0));
    TEST_ASSERT_EQUAL_FLOAT(1.0, buf.at(1));
    TEST_ASSERT_EQUAL_FLOAT(2.0, buf.at(2));
}

void test_push_over() {
    float data[2];
    CircularBuffer buf(data, 2);

    buf.push(1.0);
    buf.push(2.0);
    buf.push(3.0);

    float exp[2] = {3.0, 2.0};

    TEST_ASSERT_EQUAL_INT_MESSAGE(2, buf.count(), "Incorrect Size");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.0, buf.at(0), "Element at index 0 is incorrect");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(3.0, buf.at(1), "Element at index 1 is incorrect");
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

void test_pop_throw() {
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
    RUN_TEST(test_pop_throw);

    RUN_TEST(test_at_initial);
    RUN_TEST(test_at_out_of_range);
    RUN_TEST(test_at_after_loop);

    RUN_TEST(test_is_empty);
    RUN_TEST(test_is_empty_full);

    UNITY_END();
}