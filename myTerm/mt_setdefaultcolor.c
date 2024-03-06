#include <myTerm.h>

int
mt_setdefaultcolor (void)
{
  fflush (stdout);
  if (write (STDOUT_FILENO, "\033[0m", 4) == -1)
    return -1;
  return 0;
}