#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/defs.hpp>

namespace {

using cucumber::ScenarioScope;
using namespace testing;

struct AppContext {
};

GIVEN("^succeed$") {
SUCCEED();
}

}
