#include <DebounceFilter.hpp>
#include <unity.h>
#include <initializer_list>
#include <cstddef>

constexpr std::size_t min_value_repetitions_for_filter_transition = 15;

void setUp() {}
void tearDown() {}

void test_debounce_filter_transitions() {

    // Given: a debounce filter with `min_value_repetitions_for_filter_transition` to change its value
    //  and initial value false
    DebounceFilter debounce_filter(min_value_repetitions_for_filter_transition, false);

    // When: same value is fed into filter very often
    for (size_t i=0; i<2; i++) {
        const auto value_transition = debounce_filter.update(false);
        // Then: no transition shall be triggered
        TEST_ASSERT_EQUAL(DebounceFilter::ValueTransition::no_transition, value_transition);
    }

    // When: opposite value (true) is fed in less often than <min_value_repetitions_for_filter_transition>
    for (size_t fed_in_count : {1, 14}) {
        for (size_t i=0; i<fed_in_count; i++) {
            const auto value_transition = debounce_filter.update(true);
            // Then: no transition shall be triggered
            TEST_ASSERT_EQUAL(DebounceFilter::ValueTransition::no_transition, value_transition);
        }

        // and the initial value is fed in afterwards, to reset
        const auto value_transition = debounce_filter.update(false);
        TEST_ASSERT_EQUAL(DebounceFilter::ValueTransition::no_transition, value_transition);
    }

    // When: opposite value occurs with enough repetitions
    for (size_t i=0; i<min_value_repetitions_for_filter_transition; i++) {
        TEST_ASSERT_EQUAL(DebounceFilter::ValueTransition::no_transition, debounce_filter.update(true));
    }
    const auto value_transition = debounce_filter.update(true);

    // Then: a transition has to be triggered
    TEST_ASSERT_EQUAL(DebounceFilter::ValueTransition::transition_up, value_transition);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_debounce_filter_transitions);

    UNITY_END();
}
