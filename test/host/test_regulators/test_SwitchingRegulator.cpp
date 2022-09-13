#include <unity.h>
#include <SwitchingRegulator.hpp>

constexpr bool ON = true, OFF = false;

void setUp() {}
void tearDown() {}

void test_SwitchingRegulator () {
    // Given: a Switching Regulator with limit_up 0.0 and limit down -1.0
    SwitchingRegulator reg(0.0f, -1.0f);

    TEST_ASSERT_EQUAL(ON, reg.calc_new_command(-2.0f));
    TEST_ASSERT_EQUAL(OFF, reg.calc_new_command(0.5f));
    TEST_ASSERT_EQUAL(OFF, reg.calc_new_command(-0.5f));
    TEST_ASSERT_EQUAL(ON, reg.calc_new_command(-1.5f));
    TEST_ASSERT_EQUAL(ON, reg.calc_new_command(-0.5f));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_SwitchingRegulator);

    UNITY_END();
}
