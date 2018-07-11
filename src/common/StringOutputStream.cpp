#include "StringOutputStream.h"

namespace Common {

StringOutputStream::StringOutputStream(std::string& out) : out(out) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
size_t StringOutputStream::writeSome(const void* data, size_t size) {
  out.append(static_cast<const char*>(data), size);
  return size;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
