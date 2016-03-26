#ifndef SKELETON_ICOMMAND_H
#define SKELETON_ICOMMAND_H

namespace Controller {

class ICommand {
public:
  virtual void execute(std::string const & command) = 0;
};

}

#endif //SKELETON_ICOMMAND_H
