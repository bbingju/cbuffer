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
    TEST_ASSERT_EQUAL_INT32(1, test_buffer.head);
    TEST_ASSERT_EQUAL_INT32(0, test_buffer.tail);

    cbuffer_push(&test_buffer, 2);
    TEST_ASSERT_EQUAL_INT32(2, test_buffer.head);
    TEST_ASSERT_EQUAL_INT32(0, test_buffer.tail);

    cbuffer_push(&test_buffer, 3);
    TEST_ASSERT_EQUAL_INT32(3, test_buffer.head);
    TEST_ASSERT_EQUAL_INT32(0, test_buffer.tail);

    TEST_ASSERT_EQUAL_INT32(-1, cbuffer_push(&test_buffer, 4));
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
    TEST_ASSERT_EQUAL_UINT8(10, data);
    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(11, data);
    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(12, data);

    TEST_ASSERT_TRUE(cbuffer_isempty(&test_buffer));
}

TEST(cbuffer, cbuffer_ShouldElementsPushedAndPoppedCorrectly)
{
    uint8_t data;

    cbuffer_reset(&test_buffer);

    cbuffer_push(&test_buffer, 'a');
    cbuffer_peek(&test_buffer, &data, 0);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'b');
    cbuffer_peek(&test_buffer, &data, 0);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'c');
    cbuffer_peek(&test_buffer, &data, 0);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'a');

    cbuffer_push(&test_buffer, 'd');
    cbuffer_peek(&test_buffer, &data, 0);
    TEST_ASSERT_EQUAL_UINT8(data, 'b');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'b');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'c');

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8(data, 'd');

    TEST_ASSERT_TRUE(cbuffer_isempty(&test_buffer));
}

TEST(cbuffer, cbuffer_ShouldElementsPushedAndPeekedByIndexCorrectly)
{
    uint8_t data;

    cbuffer_reset(&test_buffer);

    cbuffer_push(&test_buffer, 'a');
    TEST_ASSERT_EQUAL_INT32(1, cbuffer_len(&test_buffer));

    cbuffer_push(&test_buffer, 'b');
    TEST_ASSERT_EQUAL_INT32(2, cbuffer_len(&test_buffer));

    cbuffer_push(&test_buffer, 'c');
    TEST_ASSERT_EQUAL_INT32(3, cbuffer_len(&test_buffer));

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8('a', data);
    TEST_ASSERT_EQUAL_INT32(2, cbuffer_len(&test_buffer));

    cbuffer_push(&test_buffer, 'd');
    TEST_ASSERT_EQUAL_INT32(3, cbuffer_len(&test_buffer));

    cbuffer_peek(&test_buffer, &data, 0);
    TEST_ASSERT_EQUAL_UINT8('b', data);

    cbuffer_peek(&test_buffer, &data, 1);
    TEST_ASSERT_EQUAL_UINT8('c', data);

    cbuffer_peek(&test_buffer, &data, 2);
    TEST_ASSERT_EQUAL_UINT8('d', data);

    cbuffer_pop(&test_buffer, &data);
    TEST_ASSERT_EQUAL_UINT8('b', data);
    TEST_ASSERT_EQUAL_INT32(2, cbuffer_len(&test_buffer));

    cbuffer_push(&test_buffer, 'e');
    TEST_ASSERT_EQUAL_INT32(3, cbuffer_len(&test_buffer));

    /* TEST_ASSERT_EQUAL_INT32(cbuffer_len(&test_buffer), 3); */
}
