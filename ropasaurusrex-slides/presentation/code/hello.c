// gcc -m32 -O0 -o hello hello.c

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello world!\n I've %d args!", argc);
  return EXIT_SUCCESS;
}
