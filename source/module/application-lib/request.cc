#include "application/request.h"

namespace Module {

template<>
void Request<void>::dispatch()
{
  _request();
  _promise.set_value();
}

}
