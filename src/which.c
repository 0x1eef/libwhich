#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static char* join(const char *path, const char *progname);
static char* append(char *dst, char *src);
static int is_executable(char *path);

static const char* COLON = ":";
static const char SEP = '/';

/**
  When an executable by the name 'progname' can be found
  on $PATH then this function will allocate and return
  an absolute path to 'progname', as a char pointer.
  Otherwise, NULL is returned.
*/
char*
which(const char *progname)
{
  char *penv, *path;
  penv = strdup(getenv("PATH"));
  if (penv == NULL) {
    return NULL;
  } else if (progname == NULL) {
    free(penv);
    return NULL;
  } else {
    path = strtok(penv, COLON);
    while (path != NULL) {
      char *exe;
      exe = join(path, progname);
      if (exe == NULL) {
        free(penv);
        return NULL;
      } else if (is_executable(exe)) {
        free(penv);
        return exe;
      } else {
        free(exe);
      }
      path = strtok(NULL, COLON);
    }
    free(penv);
    return NULL;
  }
}

/**
  When an executable by the name of 'progname' can be found
  on $PATH, then this function returns 0. Otherwise -1 is
  returned. Unlike its counterpart "which", this function
  does not leave memory allocated on the heap that the caller
  should eventually free.
*/
int
whichp(const char *progname)
{
  char *path;
  path = which(progname);
  if (path == NULL) {
    return -1;
  } else {
    free(path);
    return 0;
  }
}

static char*
join(const char *path, const char *progname)
{
  char *str, *p;
  size_t len1, len2;
  len1 = strlen(path);
  len2 = strlen(progname);
  str = malloc(sizeof(char[len1 + len2 + 2]));
  if (str == NULL) {
    return NULL;
  } else {
    p = append(str, (char*) path);
    p = append(p, (char*) &SEP);
    p = append(p, (char*) progname);
    *p = '\0';
    return str;
  }
}

static char*
append(char *dst, char *src)
{
  while(*src != '\0') {
    *dst++ = *src++;
  }
  if (*dst == SEP) {
    dst--;
  }
  return dst;
}

static int
is_executable(char *path)
{
  struct stat s;
  if (stat(path, &s) == 0) {
    return s.st_mode & S_IXUSR ||
           s.st_mode & S_IXGRP ||
           s.st_mode & S_IXOTH;
  } else {
    errno = 0;
    return 0;
  }
}
