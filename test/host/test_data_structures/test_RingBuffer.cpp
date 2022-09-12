#include <unity.h>
#include <RingBuffer.hpp>

void setUp() {
}

void tearDown() {
}

void test_MiniRingBuffer() {
    RingBuffer<int, 1> ringbuffer;

    int tmp;

    // When: we read from the empty buffer, Then: the operation fails
    TEST_ASSERT_FALSE(ringbuffer.get(&tmp));

    // When: free elements are requested, Then: we get the buffer size of one
    TEST_ASSERT_EQUAL(1, ringbuffer.count_free());

    // When: first element is added, Then: the operation succeds
    TEST_ASSERT_TRUE(ringbuffer.put(3));

    // and Then: there are no free elements left
    TEST_ASSERT_EQUAL(0, ringbuffer.count_free());

    // When: second element is added, Then: buffer is full -> operation fails
    TEST_ASSERT_FALSE(ringbuffer.put(3));

    // When: we read from filled buffer, Then: we should get the stored value and 1 free slot in buffer
    TEST_ASSERT_TRUE(ringbuffer.get(&tmp));
    TEST_ASSERT_EQUAL(3, tmp);
    TEST_ASSERT_EQUAL(1, ringbuffer.count_free());
}

void test_putget() {
    RingBuffer<int, 15> ringbuffer;

    for (size_t i=0; i<2; i++) {
        size_t counter = 0U;

        while(ringbuffer.put(counter++));

        int tmp;
        counter = 0U;
        while (ringbuffer.get(&tmp)) {
            TEST_ASSERT_EQUAL(counter, tmp);
            counter++;
        }
    }
}

void test_overwrite() {
    static constexpr size_t ringbuffer_size = 5;
    static constexpr int dummy_value = 2, 
        dummy_overwrite_value = 4;
    
    RingBuffer<int, ringbuffer_size> ringbuffer;

    for (size_t i=0; i<ringbuffer_size; i++) {
        ringbuffer.put(dummy_value);
    }

    for (size_t i=0; i<ringbuffer_size; i++) {
        ringbuffer.force_put(dummy_overwrite_value);
    }

    int tmp;
    while (ringbuffer.get(&tmp)) {
        TEST_ASSERT_EQUAL(dummy_overwrite_value, tmp);
        break;
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_MiniRingBuffer);
    RUN_TEST(test_putget);
    RUN_TEST(test_overwrite);

    UNITY_END();
}
