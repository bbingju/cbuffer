#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(cbuffer)
{
    RUN_TEST_CASE(cbuffer, cbuffer_ShouldBufferIsFull);
    RUN_TEST_CASE(cbuffer, cbuffer_ShouldNumberOfElementsCorrectly);
    RUN_TEST_CASE(cbuffer, cbuffer_ShouldElementsPoppedCorrectly);
    RUN_TEST_CASE(cbuffer, cbuffer_ShouldElementsPushedAndPoppedCorrectly);
    RUN_TEST_CASE(cbuffer, cbuffer_ShouldElementsPushedAndPeekedByIndexCorrectly);
}
