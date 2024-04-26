#include "mylib/mylib.h"

#include <stdio.h>

int mylib_test(int n)
{
  int result = n + MY_LIB_CONSTANT;
  puts("mylib_test");
  printf("n: %d\n", result);
  return result;
}