#ifndef SKELETON_PRETTY_PRINT_H
#define SKELETON_PRETTY_PRINT_H

void PrintTo(Signal signal, std::ostream* os)
{
  switch(signal) {
    default: {
      *os << "undefined value";
      break;
    }
    case Signal_Undefined: {
      *os << "Signal_Undefined";
      break;
    }
    case Signal_High: {
      *os << "Signal_High";
      break;
    }
    case Signal_Low: {
      *os << "Signal_Low";
      break;
    }
  }
}

#endif //SKELETON_PRETTY_PRINT_H
