#include <algo.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_push() {
    float data[1] = {-1.0};
    CircularBuffer buf(data, 1);

    buf.push(0.0);

    TEST_ASSERT_EQUAL_INT(1, buf.count());

    TEST_ASSERT_EQUAL_FLOAT(0.0, buf.at(0));
}

void test_push_multiple() {
    float data[3] = {-1.0, -1.0, -1.0};
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
    float data[2] = {-1.0, -1.0};
    CircularBuffer buf(data, 2);

    buf.push(1.0);
    buf.push(2.0);
    buf.push(3.0);

    TEST_ASSERT_EQUAL_INT_MESSAGE(2, buf.count(), "Incorrect Size");

    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.0, buf.at(0), "Element at index 0 is incorrect");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(3.0, buf.at(1), "Element at index 1 is incorrect");
}

void test_pop() {
    float data[1] = {-1.0};
    CircularBuffer buf(data, 1);

    buf.push(1.0);

    TEST_ASSERT_EQUAL_FLOAT(1.0, buf.pop());
}

void test_pop_empty() {
    float data[1] = {-1.0};
    CircularBuffer buf(data, 1);

    try {
        buf.pop();
        TEST_FAIL_MESSAGE("Popping on empty buf should throw");
    }
    catch (...) {}
}

void test_pop_multiple() {
    float data[2] = {-1.0, -1.0};
    CircularBuffer buf(data, 2);

    buf.push(1.0);
    buf.push(2.0);
    buf.push(3.0);

    TEST_ASSERT_EQUAL_FLOAT(3.0, buf.pop());
    TEST_ASSERT_EQUAL_FLOAT(2.0, buf.pop());
}

void test_at_initial() {
    float data[1] = {-1.0};
    CircularBuffer buf(data, 1);

    try {
        buf.at(0);
        TEST_FAIL_MESSAGE("Accessing index 0 of empty buffer should throw");
    }
    catch (...) {}
}

void test_at_out_of_range() {
    float data[2] = {-1.0, -1.0};
    CircularBuffer buf(data, 2);

    buf.push(0);

    try {
        buf.at(1);
        TEST_FAIL_MESSAGE("Accessing at index 1 of buffer with size 1 should throw");
    }
    catch (...) {}

    try {
        buf.at(-1);
        TEST_FAIL_MESSAGE("Accessing at index -1 of buffer with size 1 should throw");
    }
    catch (...) {}
}

void test_at_negative() {
    float data[3] = {-1.0, -1.0, -1.0};
    CircularBuffer buf(data, 3);

    buf.push(0);
    buf.push(1);
    buf.push(2);
    buf.push(4);

    TEST_ASSERT_EQUAL_FLOAT(1, buf.at(0));
    TEST_ASSERT_EQUAL_FLOAT(4, buf.at(-1));
}

void test_is_empty() {
    float data[1];
    CircularBuffer buf(data, 1);

    TEST_ASSERT(buf.isEmpty());
}

void test_is_not_empty() {
    float data[1];
    CircularBuffer buf(data, 1);

    buf.push(1);

    TEST_ASSERT_FALSE(buf.isEmpty());
}

void test_avg_single() {
    float data[1];
    CircularBuffer buf(data, 1);

    buf.push(1);

    TEST_ASSERT_EQUAL_FLOAT(buf.avg(), 1);
}

void test_avg_mult() {
    float data[2];
    CircularBuffer buf(data, 2);

    buf.push(1);
    
    TEST_ASSERT_EQUAL_FLOAT(buf.avg(), 1);

    buf.push(3);

    TEST_ASSERT_EQUAL_FLOAT(buf.avg(), 2);
}

void test_avg_pop() {
    float data[2];
    CircularBuffer buf(data, 2);

    buf.push(1);

    buf.push(3);
    buf.pop();

    TEST_ASSERT_EQUAL_FLOAT(buf.avg(), 1);
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
    RUN_TEST(test_at_negative);

    RUN_TEST(test_is_empty);
    RUN_TEST(test_is_not_empty);

    RUN_TEST(test_avg_single);
    RUN_TEST(test_avg_mult);
    RUN_TEST(test_avg_pop);

    UNITY_END();
}