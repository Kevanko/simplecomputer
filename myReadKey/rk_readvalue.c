#include <myReadKey.h>

int
rk_readvalue (int *value, int timeout)
{
  char buffer[10];
  fgets (buffer, 10, stdin);
  fflush (stdin);
  int number;
  char *tmp;
  if (buffer[0] == '+')
    {
      number = strtol (&buffer[1], &tmp, 16);
      if (number > 0x3FFF)
        {
          return -1;
        }
      *value = number;
    }
  else
    {
      number = strtol (buffer, &tmp, 16);
      if (number > 0x3FFF)
        {
          return -1;
        }
      *value = number;
    }
  return 0;
}