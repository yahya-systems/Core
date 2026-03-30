#pragma once
#include <cstdlib>

template <typename T> constexpr bool is_power_of_two(T n) noexcept {
  // A power of two must be greater than 0
  // and have only one bit set (n & (n-1) == 0)
  return n > 0 && (n & (n - 1)) == 0;
}

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
