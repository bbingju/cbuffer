#include "../cbuffer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(cbuffer);

CBUFFER_DEF_STATIC(test_buffer, 4);

TEST_SETUP(cbuffer)
{
}

TEST_TEAR_DOWN(cbuffer)
{
}

TEST(cbuffer, cbuffer_ShouldBufferIsFull)
{
    /* uint8_t data; */
    cbuffer_reset(&test_buffer);
    cbuffer_push(&test_buffer, 1);
    cbuffer_push(&test_buffer, 2);
    cbuffer_push(&test_buffer, 3);

    TEST_ASSERT_EQUAL_INT32(cbuffer_push(&test_buffer, 4), -1);
    TEST_ASSERT_TRUE(cbuffer_isfull(&test_buffer));
}

TEST(cbuffer, cbuffer_ShouldElementsPoppedCorrectly)
{
    uint8_t data;

    cbuffer_reset(&test_buffer);
    cbuffer_push(&test_buffer, 10);
    cbuffer_push(&test_buffer, 11);
    cbuffer_push(&test_buffer, 12);

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 10);
    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 11);
    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 12);

    TEST_ASSERT_TRUE(cbuffer_isempty(&test_buffer));
}

TEST(cbuffer, cbuffer_ShouldElementsPushedAndPoppedCorrectly)
{
    uint8_t data;

    cbuffer_reset(&test_buffer);

    cbuffer_push(&test_buffer, 'a');
    cbuffer_peek(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'b');
    cbuffer_peek(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'c');
    cbuffer_peek(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'd');
    cbuffer_peek(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'b');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'b');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'c');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'd');

    TEST_ASSERT_TRUE(cbuffer_isempty(&test_buffer));
}
