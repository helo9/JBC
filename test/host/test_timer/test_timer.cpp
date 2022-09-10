#include <unity.h>
#include <Timer.hpp>

constexpr millis_t interval_ms = 25;

Timer *timer;

void setUp() {
    timer = new Timer(interval_ms);
}

void tearDown() {
    delete timer;
}

void timer_not_started() {
    // Given: A not started timer

    // When: any time has passed
    // Then: the timer shall never be expired
    // ..

    timer->update(0);
    TEST_ASSERT_FALSE(timer->is_expired());

    timer->update(1);
    TEST_ASSERT_FALSE(timer->is_expired());

    timer->update(max_millis_t);
    TEST_ASSERT_FALSE(timer->is_expired());    
}

void timer_expired() {
    // Given: a Timer started at time 0
    timer->start(0);

    // When: the interval time has passed
    timer->update(interval_ms + 1);

    // Then: the timer shall be expired
    TEST_ASSERT_TRUE(timer->is_expired());
}

void timer_overflow() {
    // Given: a timer started at maximum timer value
    timer->start(max_millis_t);

    // When: the time variable overflows and starts at 0
    timer->update(0);

    // Then: the timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired()); 

    // When: 1ms has passed since overflow
    timer->update(1);

    // Then: the timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: the interval time has passed
    timer->update(interval_ms + 1);

    // Then: the timer shall be expired
    TEST_ASSERT_TRUE(timer->is_expired());
}


void timer_overflow2() {
    // Given: a timer started at almost the maximum timer value
    timer->start(max_millis_t - 5);

    // When: the time variable overflows and starts at 0
    timer->update(0);

    // Then: the timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired()); 

    // When: 1ms has passed since overflow
    timer->update(1);

    // Then: the timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: the interval time has passed
    timer->update(interval_ms + 5);

    // Then: the timer shall be expired
    TEST_ASSERT_TRUE(timer->is_expired());
}

void test_multiple_expirations() {
    // Given: a timer started at time 0
    timer->start(0);

    // When: exactly one interval has passed
    timer->update(interval_ms);

    // Then: timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: slightly more time has passed than interval
    timer->update(interval_ms + 1);

    // Then: the timer shall be expired
    TEST_ASSERT_TRUE(timer->is_expired());

    // When: the timer expiration was reset
    timer->reset_expired();

    // Then: the timer shall not be expired anymore
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: reset happened and no time passed
    // Then: the timer shall not be expired
    timer->update(interval_ms + 1);
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: some time has passed, but not yet the complete second interval
    timer->update(2 * interval_ms - 1);

    // Then: the timer shall not be expired
    TEST_ASSERT_FALSE(timer->is_expired());

    // When: enough time has passed, so second interval was passed
    timer->update(2 * interval_ms + 2);
    
    // Then: the timer shall be expired
    TEST_ASSERT_TRUE(timer->is_expired());
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(timer_not_started);
    RUN_TEST(timer_expired);
    RUN_TEST(timer_overflow);
    RUN_TEST(timer_overflow2);
    RUN_TEST(test_multiple_expirations);

    UNITY_END();
}
