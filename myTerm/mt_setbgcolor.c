#include <myTerm.h>
#include <string.h>

int
mt_setbgcolor (enum colors color)
{
  char buf[32];
  snprintf (buf, sizeof (buf), "\033[48;5;%dm", color);
  fflush (stdout);
  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    return -1;
  return 0;
}