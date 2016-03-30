#include <gmock/gmock.h>

#include <application/scheduler.h>

using namespace testing;

namespace {

TEST(A_Scheduler, DISABLED_executes_a_request_when_started)
{
  FAIL();
}

TEST(A_Scheduler, DISABLED_executes_requests_in_sequence)
{
  // uint32_t value = 0;
  // uint32_t const a = 1000;
  // uint32_t const b = 1000;
  // std::thread([]{ testee.schedule([]{ for(uint32_t i = 0; i < a; ++i){ ++value; } }); });
  // std::thread([]{ testee.schedule([]{ for(uint32_t i = 0; i < b; ++i){ ++value; } }); });
  // ASSERT_THAT(value, Eq(a + b));
  FAIL();
}

TEST(A_Scheduler, DISABLED_ignores_a_request_when_not_started)
{
  FAIL();
}

TEST(A_Scheduler, DISABLED_ignores_a_request_when_stopped)
{
  FAIL();
}

}

