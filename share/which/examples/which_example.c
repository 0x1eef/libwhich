#include <stdio.h>
#include <stdlib.h>
#include <which.h>

int
main()
{
  char *path;
  path = which("ls");
  if (path != NULL) {
    printf("ok: %s\n", path);
    free(path);
  } else {
    printf("error: 'ls' not found\n");
  }
  return EXIT_SUCCESS;
}
