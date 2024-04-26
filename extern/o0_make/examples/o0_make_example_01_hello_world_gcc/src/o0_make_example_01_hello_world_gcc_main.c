#include <stdio.h>

int main(int argc, char* argv[])
{
  puts("Hello, World! Command-line args:");

  for (int i = 0; i != argc; ++i)
  {
    printf("%s\n", argv[i]);
  }

  puts("Bye, World!");
  return 0;
}
