#include <Timer.hpp>
#include <unity.h>

constexpr millis_t interval = 1000UL;

volatile bool expired_flag = false;

void set_flag() {
    expired_flag = true;
}

void reset_flag() {
    expired_flag = false;
}

Timer timer([](){set_flag();});

void setUp() {
    reset_flag();
}

void tearDown() {
    timer.stop();
}

void timer_not_started() {
    // Given: A not started timer
    timer;

    // When: any amount of SysTick calls happend
    for (size_t i; i<(interval-1); i++) {
        Timer::onSysTick();
        
        // Then: the timer shall never be expired
        TEST_ASSERT_FALSE(expired_flag);
    }    
}

void test_timer_expires() {

    timer.start(interval);

    for (size_t i=0; i<(interval-1); i++) {
        Timer::onSysTick();
        TEST_ASSERT_FALSE(expired_flag);
    }

    Timer::onSysTick();

    TEST_ASSERT_TRUE(expired_flag);
}

void test_periodic_timer() {

    static constexpr size_t times_to_repeat = 50;

    timer.start(interval);

    for (size_t i=0; i<times_to_repeat; i++) {
        for (size_t i=0; i<(interval-1); i++) {
            Timer::onSysTick();
            TEST_ASSERT_FALSE(expired_flag);
        }
        Timer::onSysTick();
        TEST_ASSERT_TRUE(expired_flag);

        reset_flag();       
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(timer_not_started);
    RUN_TEST(test_timer_expires);
    RUN_TEST(test_periodic_timer);

    UNITY_END();
}
