#include <stdio.h>
#include <stdlib.h>
#include <which.h>

int
main()
{
  if (whichp("ls") == 0) {
    printf("'ls' executable found within $PATH\n");
  } else {
    printf("'ls' executable not found within $PATH\n");
  }
  return EXIT_SUCCESS;
}
