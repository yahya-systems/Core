#include "Core/containers.hpp"
#include "stdio.h"
#include <string.h>

char *get_next_line_sim(char *buff) {
  static int ptr = 0;
  int len = 0;
  while (buff[ptr + len] != '\n') {
    len++;
  }
  char *temp = (char *)malloc(len += 1);
  memcpy(temp, &buff[ptr], len + 1);
  ptr += len + 1;
  return temp;
}

// "nigga\n brr"
int *ft_range(int start, int end) {
  uint32_t length = abs((end - start)) + 1;
  int *buffer = (int *)malloc(length * sizeof(int));
  for (uint32_t i = 0; i < length; i++) {
    buffer[i] = (end >= start) ? i + start : start - i;
  }
  return buffer;
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// ft_range(1, 5) returns [1, 2, 3, 4, 5]
// ft_range(3, 2) returns [3, 2]

int main() {
  int *range = ft_range(3, 2);
  print_array(range, 2);
  free(range);
  return 0;
}
