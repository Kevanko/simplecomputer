#include <myTerm.h>
#include <string.h>

int
mt_setcursorvisible (int value)
{
  char buf[32];
  snprintf (buf, sizeof (buf), "\033[?25%c", value ? 'h' : 'l');
  fflush (stdout);
  if (write (STDOUT_FILENO, buf, strlen (buf)) == -1)
    return -1;
  return 0;
}