#include <myTerm.h>
#include <string.h>

int
mt_setfgcolor (enum colors color)
{
  char buf[32];
  snprintf (buf, sizeof (buf), "\033[38;5;%dm", color);
  fflush (stdout);
  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    return -1;
  return 0;
}