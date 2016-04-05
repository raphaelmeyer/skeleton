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
  Module::Request<void> request{[&]{ executed = true; }};
  testee.schedule(request);

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

TEST(A_Scheduler, executes_requests_in_sequence)
{
  Module::Scheduler testee;
  testee.start();

  bool idle = true;

  auto function = [&]{
    if (!idle) {
      return false;
    }

    idle = false;
    std::this_thread::yield();
    idle = true;

    return true;
  };

  size_t number_of_threads = 20;

  std::vector<Module::Request<bool>> requests;
  for(size_t i = 0; i < number_of_threads; ++i) {
    requests.emplace_back(Module::Request<bool>(function));
  }

  std::vector<std::thread> threads;
  for(auto & request : requests) {
    threads.emplace_back([&]{ testee.schedule(request); });
  }

  for(auto & thread : threads) {
    thread.join();
  }

  for(auto & request : requests) {
    bool const request_was_executed_in_sequence = request.get_future().get();
    ASSERT_TRUE(request_was_executed_in_sequence);
  }

}

}

