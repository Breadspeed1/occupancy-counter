#include <unity.h>
#include <algo.h>
#include <stdio.h>

void setUp(void) {}

void tearDown(void) {}

void test_test() {
    puts("Erm... Guys?");
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_test);

    UNITY_END();
}