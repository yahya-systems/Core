#include "Core/containers.hpp"
#include "stdio.h"

int main() {
  core::array arr{1, 2, 3, 4, 5};
  printf("array size is %lu\n", arr.size());
  uint32_t u = *arr.at(8).unwrap();
  return 0;
}
