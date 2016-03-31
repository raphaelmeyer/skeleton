#include <gmock/gmock.h>

#include <application/scheduler.h>
#include <application/request.h>

using namespace testing;

namespace {

TEST(A_Scheduler, executes_a_request_when_started)
{
  Module::Scheduler testee;

  testee.start();

  bool executed = false;
  Module::Request<uint32_t> request{[&]{ executed = true; return 0; }};
  testee.schedule(request);

  ASSERT_TRUE(executed);
}

TEST(A_Scheduler, DISABLED_executes_a_request_when_started)
{
  // Use this to replace test with same name

  Module::Scheduler testee;

  testee.start();

  bool executed = false;
  //Module::Request<void> request{[&]{ executed = true; }};
  //testee.schedule(request);

  ASSERT_TRUE(executed);
}


TEST(A_Scheduler, returns_a_future_for_the_result_of_the_request)
{
  Module::Scheduler testee;

  testee.start();

  uint32_t const expected = 42;

  auto result = testee.schedule([](){ return expected; });

  ASSERT_THAT(result.get(), Eq(expected));
}

TEST(A_Scheduler, returns_a_future_with_the_same_type_as_the_result_of_the_request)
{
  Module::Scheduler testee;
  testee.start();

  //float_t const floating_point = 3.14;
  //auto float_result = testee.schedule([=]{ return floating_point; });

  //ASSERT_THAT(float_result.get(), FloatEq(floating_point));

  std::string const string = "42";
  auto string_result = testee.schedule([=]{ return string; });

  ASSERT_THAT(string_result.get(), StrEq(string));
}


TEST(A_Scheduler, DISABLED_forwards_arbitrary_parameters_to_the_request) {
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

