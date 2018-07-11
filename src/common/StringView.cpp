#include "StringView.h"
#include <limits>

namespace Common {

const StringView::Size StringView::INVALID = std::numeric_limits<StringView::Size>::max();
const StringView StringView::EMPTY(reinterpret_cast<Object*>(1), 0);
const StringView StringView::NIL(nullptr, 0);
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::StringView()
#ifndef NDEBUG
  : data(nullptr), size(INVALID) // In debug mode, fill in object with invalid state (undefined).
#endif
{
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::StringView(const Object* stringData, Size stringSize) : data(stringData), size(stringSize) {
  assert(data != nullptr || size == 0);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::StringView(const std::string& string) : data(string.data()), size(string.size()) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::StringView(const StringView& other) : data(other.data), size(other.size) {
  assert(data != nullptr || size == 0);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::~StringView() {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView& StringView::operator=(const StringView& other) {
  assert(other.data != nullptr || other.size == 0);
  data = other.data;
  size = other.size;
  return *this;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::operator std::string() const {
  return std::string(data, size);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object* StringView::getData() const {
  assert(data != nullptr || size == 0);
  return data;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::Size StringView::getSize() const {
  assert(data != nullptr || size == 0);
  return size;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::isEmpty() const {
  assert(data != nullptr || size == 0);
  return size == 0;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::isNil() const {
  assert(data != nullptr || size == 0);
  return data == nullptr;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object& StringView::operator[](Size index) const {
  assert(data != nullptr || size == 0);
  assert(index < size);
  return *(data + index);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object& StringView::first() const {
  assert(data != nullptr || size == 0);
  assert(size > 0);
  return *data;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object& StringView::last() const {
  assert(data != nullptr || size == 0);
  assert(size > 0);
  return *(data + (size - 1));
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object* StringView::begin() const {
  assert(data != nullptr || size == 0);
  return data;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
const StringView::Object* StringView::end() const {
  assert(data != nullptr || size == 0);
  return data + size;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator==(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size == other.size) {
    for (Size i = 0;; ++i) {
      if (i == size) {
        return true;
      }

      if (!(*(data + i) == *(other.data + i))) {
        break;
      }
    }
  }

  return false;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator!=(StringView other) const {
  return !(*this == other);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator<(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  Size count = other.size < size ? other.size : size;
  for (Size i = 0; i < count; ++i) {
    Object char1 = *(data + i);
    Object char2 = *(other.data + i);
    if (char1 < char2) {
      return true;
    }

    if (char2 < char1) {
      return false;
    }
  }

  return size < other.size;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator<=(StringView other) const {
  return !(other < *this);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator>(StringView other) const {
  return other < *this;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::operator>=(StringView other) const {
  return !(*this < other);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::beginsWith(const Object& object) const {
  assert(data != nullptr || size == 0);
  if (size == 0) {
    return false;
  }

  return *data == object;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::beginsWith(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size >= other.size) {
    for (Size i = 0;; ++i) {
      if (i == other.size) {
        return true;
      }

      if (!(*(data + i) == *(other.data + i))) {
        break;
      }
    }
  }

  return false;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::contains(const Object& object) const {
  assert(data != nullptr || size == 0);
  for (Size i = 0; i < size; ++i) {
    if (*(data + i) == object) {
      return true;
    }
  }

  return false;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::contains(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size >= other.size) {
    Size i = size - other.size;
    for (Size j = 0; !(i < j); ++j) {
      for (Size k = 0;; ++k) {
        if (k == other.size) {
          return true;
        }

        if (!(*(data + j + k) == *(other.data + k))) {
          break;
        }
      }
    }
  }

  return false;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::endsWith(const Object& object) const {
  assert(data != nullptr || size == 0);
  if (size == 0) {
    return false;
  }

  return *(data + (size - 1)) == object;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
bool StringView::endsWith(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size >= other.size) {
    Size i = size - other.size;
    for (Size j = 0;; ++j) {
      if (j == other.size) {
        return true;
      }

      if (!(*(data + i + j) == *(other.data + j))) {
        break;
      }
    }
  }

  return false;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::Size StringView::find(const Object& object) const {
  assert(data != nullptr || size == 0);
  for (Size i = 0; i < size; ++i) {
    if (*(data + i) == object) {
      return i;
    }
  }

  return INVALID;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::Size StringView::find(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size >= other.size) {
    Size i = size - other.size;
    for (Size j = 0; !(i < j); ++j) {
      for (Size k = 0;; ++k) {
        if (k == other.size) {
          return j;
        }

        if (!(*(data + j + k) == *(other.data + k))) {
          break;
        }
      }
    }
  }

  return INVALID;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::Size StringView::findLast(const Object& object) const {
  assert(data != nullptr || size == 0);
  for (Size i = 0; i < size; ++i) {
    if (*(data + (size - 1 - i)) == object) {
      return size - 1 - i;
    }
  }

  return INVALID;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView::Size StringView::findLast(StringView other) const {
  assert(data != nullptr || size == 0);
  assert(other.data != nullptr || other.size == 0);
  if (size >= other.size) {
    Size i = size - other.size;
    for (Size j = 0; !(i < j); ++j) {
      for (Size k = 0;; ++k) {
        if (k == other.size) {
          return i - j;
        }

        if (!(*(data + (i - j + k)) == *(other.data + k))) {
          break;
        }
      }
    }
  }

  return INVALID;
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::head(Size headSize) const {
  assert(data != nullptr || size == 0);
  assert(headSize <= size);
  return StringView(data, headSize);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::tail(Size tailSize) const {
  assert(data != nullptr || size == 0);
  assert(tailSize <= size);
  return StringView(data + (size - tailSize), tailSize);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::unhead(Size headSize) const {
  assert(data != nullptr || size == 0);
  assert(headSize <= size);
  return StringView(data + headSize, size - headSize);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::untail(Size tailSize) const {
  assert(data != nullptr || size == 0);
  assert(tailSize <= size);
  return StringView(data, size - tailSize);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::range(Size startIndex, Size endIndex) const {
  assert(data != nullptr || size == 0);
  assert(startIndex <= endIndex && endIndex <= size);
  return StringView(data + startIndex, endIndex - startIndex);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
StringView StringView::slice(Size startIndex, Size sliceSize) const {
  assert(data != nullptr || size == 0);
  assert(startIndex <= size && startIndex + sliceSize <= size);
  return StringView(data + startIndex, sliceSize);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
