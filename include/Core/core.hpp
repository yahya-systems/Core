#pragma once
#include <cstdlib>

namespace core {

template <typename T> struct Result {
  union {
    T value;
    const char *error = nullptr;
  };
  // Return the value in case ok, abord if not.
  T &unwrap() {
    if (error) [[unlikely]] {
      abort();
    }
    return value;
  }
};

template <typename T>
constexpr inline Result<T> makeResult(bool ok, const T &val,
                                      const char *errMsg) {
  if (ok) {
    return Result<T>{.val = val};
  } else {
    return Result<T>{.error = errMsg};
  }
}

} // namespace core
