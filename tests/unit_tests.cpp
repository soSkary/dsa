#include <gtest/gtest.h>
#include "ring_buffer.hpp"

class RingBufferTest : public testing::Test
{
protected:
    // void SetUp() override
    // {

    // }

    soskary::Ring_buffer<int> test_RB;
};
// RingBuffer
TEST_F(RingBufferTest, accessingElements) {
    EXPECT_EQ(test_RB.size(), 0);
    
}
