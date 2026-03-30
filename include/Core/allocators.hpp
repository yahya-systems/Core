#pragma once

#include "Core/core.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

// class LinearAllocator {
//   uint8_t *buffer;
//   size_t offset;
//   size_t capacity;
//
// public:
//   LinearAllocator(size_t size) : offset(0), capacity(size) {
//     buffer = (uint8_t *)malloc(size);
//   }
//
//   void *alloc(size_t size, size_t align = 8) {
//     size_t aligned = (offset + align - 1) & ~(align - 1);
//     if (aligned + size > capacity)
//       abort();
//     offset = aligned + size;
//     return buffer + aligned;
//   }
//   void reset() { offset = 0; }
//
//   ~LinearAllocator() { free(buffer); }
// };

class LinearAllocator {
  unsigned char *buffer = nullptr;
  unsigned char *offset;
  size_t capacity;

public:
  LinearAllocator() = delete;

  LinearAllocator(size_t size) : capacity(size) {
    buffer = (unsigned char *)malloc(size);
    if (!buffer) {
      offset = nullptr;
      return;
    }
    offset = buffer;
  }

  LinearAllocator(const LinearAllocator &allocator) = delete;

  LinearAllocator(LinearAllocator &&allocator) {
    buffer = allocator.buffer;
    offset = allocator.offset;
    capacity = allocator.capacity;

    allocator.buffer = nullptr;
    allocator.offset = nullptr;
    allocator.capacity = 0;
  }

  void *alloc(size_t size, size_t alignment = 8) {
    assert(is_power_of_two(alignment));
    uintptr_t addr = (uintptr_t)offset;
    size_t padding = (alignment - (addr & (alignment - 1))) & (alignment - 1);

    if ((offset - buffer) + padding + size > capacity) {
      return nullptr;
    }

    offset += padding;
    void *result = offset;
    offset += size;

    return result;
  }

  void reset() { offset = buffer; }

  int expand(size_t size) {
    if (size <= capacity) {
      return 0;
    }

    capacity = size;
    size_t _offset = offset - buffer;

    void *temp = realloc(buffer, capacity);
    if (!temp) {
      return -1;
    }
    buffer = (unsigned char *)temp;
    offset = buffer + _offset;
    return 0;
  }

  ~LinearAllocator() { free(buffer); }
};

class StackAllocator {
  unsigned char *buffer = nullptr;
  unsigned char *offset;
  size_t capacity;

public:
  StackAllocator() = delete;

  StackAllocator(size_t size) : capacity(size) {
    buffer = (unsigned char *)malloc(size);
    if (!buffer) {
      offset = nullptr;
      return;
    }
    offset = buffer;
  }

  StackAllocator(const LinearAllocator &allocator) = delete;

  StackAllocator(StackAllocator &&allocator) {
    buffer = allocator.buffer;
    offset = allocator.offset;
    capacity = allocator.capacity;

    allocator.buffer = nullptr;
    allocator.offset = nullptr;
    allocator.capacity = 0;
  }

  void *alloc(size_t size, size_t alignment = 8) {
    assert(is_power_of_two(alignment));
    uintptr_t addr = (uintptr_t)offset;
    size_t padding = (alignment - (addr & (alignment - 1))) & (alignment - 1);

    if ((offset - buffer) + padding + size > capacity) {
      return nullptr;
    }

    offset += padding;
    void *result = offset;
    offset += size;

    return result;
  }

  size_t marker() { return buffer - offset; }

  void freeTo(size_t marker) { offset = buffer + marker; }

  void reset() { offset = buffer; }

  int expand(size_t size) {
    if (size <= capacity) {
      return 0;
    }

    capacity = size;
    size_t _offset = offset - buffer;

    void *temp = realloc(buffer, capacity);
    if (!temp) {
      return -1;
    }
    buffer = (unsigned char *)temp;
    offset = buffer + _offset;
    return 0;
  }

  ~StackAllocator() { free(buffer); }
};
