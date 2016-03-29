#ifndef SKELETON_COMMAND_MOCK_H
#define SKELETON_COMMAND_MOCK_H

#include <gmock/gmock.h>

#include <application/icommand.h>

namespace Mock {

class Command : public Module::ICommand
{
public:
  MOCK_METHOD1(execute, void(std::string const &command));
};

} // namespace Mock

#endif //SKELETON_COMMAND_MOCK_H
