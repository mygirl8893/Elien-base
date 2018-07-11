#include "StdInputStream.h"

namespace Common {

StdInputStream::StdInputStream(std::istream& in) : in(in) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
size_t StdInputStream::readSome(void* data, size_t size) {
  in.read(static_cast<char*>(data), size);
  return in.gcount();
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
