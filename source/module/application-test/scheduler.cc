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
  Module::Request<uint32_t> request{[]{ return expected; }};
  testee.schedule(request);

  ASSERT_THAT(request.get_future().get(), Eq(expected));
}

TEST(A_Scheduler, returns_a_future_with_the_same_type_as_the_result_of_the_request)
{
  Module::Scheduler testee;
  testee.start();

  float_t const float_result = 3.14;
  Module::Request<float_t> float_request{[=]{ return float_result; }};
  testee.schedule(float_request);

  ASSERT_THAT(float_request.get_future().get(), FloatEq(float_result));

  std::string const string_result = "42";
  Module::Request<std::string> string_request{[=]{ return string_result; }};
  testee.schedule(string_request);

  ASSERT_THAT(string_request.get_future().get(), StrEq(string_result));
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

