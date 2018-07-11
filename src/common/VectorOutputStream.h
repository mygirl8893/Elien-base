#pragma once

#include <cstdint>
#include <vector>
#include "seria/IOutputStream.h"

namespace Common {

class VectorOutputStream : public IOutputStream {
public:
  VectorOutputStream(std::vector<uint8_t>& out);
  VectorOutputStream& operator=(const VectorOutputStream&) = delete;
  size_t writeSome(const void* data, size_t size) override;

private:
  std::vector<uint8_t>& out;
};

}
