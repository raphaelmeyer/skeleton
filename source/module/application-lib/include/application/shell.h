#ifndef SKELETON_SHELL_H
#define SKELETON_SHELL_H

#include "application/icommand.h"

namespace Module {

class Shell : public ICommand {
public:
  virtual void execute(std::string const & command);
};

}

#endif //SKELETON_SHELL_H
