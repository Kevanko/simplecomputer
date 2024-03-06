#include <myTerm.h>

int
mt_delline (void)
{
  fflush (stdout);
  if (write (STDOUT_FILENO, "\033[K", 3) == -1)
    return -1;
  return 0;
}