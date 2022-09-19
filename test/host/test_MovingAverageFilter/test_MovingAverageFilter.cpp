#include <unity.h>
#include <MovingAverageFilter.hpp>
#include <initializer_list>
#include <math.h>

constexpr float absolute_tolerance = 1e-5;

void setUp() {}
void tearDown() {}

void test_constant_values() {
    
    for (const auto val : {0.0f, 1.0f, -2.4f}) {
        // Given: A Moving Average Filter for floats, collecting 10 values
        MovingAverageFilter<float, 10> filter;

        // When: 10 times the same value is stored
        for (int i=0; i<10; i++) {
            filter.store(val);
        }

        // Then: The filter value should have that value
        TEST_ASSERT_TRUE(fabsf(val - filter.calculate()) < absolute_tolerance);
    }
}

void test_real_values() {
    static constexpr float test_values[] = {1.0f, 2.0f, 3.0f};
    static constexpr float expected_res[] = {0.5f, 1.5f, 2.5f};

    MovingAverageFilter<float, 2> filter;

    for (size_t i=0; i<3; i++) {
        filter.store(test_values[i]);

        TEST_ASSERT_TRUE(fabsf(expected_res[i] - filter.calculate()) < absolute_tolerance);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_constant_values);

    UNITY_END();
}
