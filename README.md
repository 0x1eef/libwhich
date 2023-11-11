## About

libwhich is a C library that provides a simple set of functions
that allow their callers to find executables within `$PATH` by
providing a program name as an argument.

## Examples

**which**

When an executable by the name 'progname' can be found
on `$PATH` then the which function will allocate and
return an absolute path to 'progname', as a char pointer.
Otherwise, NULL is returned:

``` c
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
```

**whichp**

When an executable by the name of 'progname' can be found
on `$PATH`, then this function returns 0. Otherwise -1 is
returned. Unlike its counterpart "which", this function does
not leave memory allocated on the heap that the caller should
eventually free:

``` c
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
```

## Sources

* [GitHub](https://github.com/0x1eef/libwhich/)
* [GitLab](https://gitlab.com/0x1eef/libwhich)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).

