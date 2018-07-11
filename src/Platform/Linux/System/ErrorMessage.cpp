#include "ErrorMessage.h"
#include <cerrno>
#include <cstring>

namespace System {

std::string lastErrorMessage() {
  return errorMessage(errno);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
std::string errorMessage(int err) {
  return "result=" + std::to_string(err) + ", " + std::strerror(err);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
