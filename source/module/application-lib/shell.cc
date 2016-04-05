#include "application/shell.h"

#include <cstdlib>

namespace Module {

void Shell::execute(std::string const & command) {
  std::system(command.c_str());
}

}