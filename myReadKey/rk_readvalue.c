#include <myReadKey.h>

int
rk_readvalue (int *value, int timeout)
{
  char buffer[10];
  fgets (buffer, 10, stdin);
  fflush (stdin);
  int number;
  char *tmp;

  number = strtol (buffer, &tmp, 16);
  if (number > 0x7FFF)
    {
      return -1;
    }
  *value = number;

  return 0;
}