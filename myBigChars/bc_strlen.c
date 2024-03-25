#include <myBigChars.h>

int
bc_strlen (char *str)
{
  int len = 0;
  while (*str != '\0')
    {
      if ((*str & 0xC0) != 0x80)
        {
          len++;
        }
      str++;
    }
  return len;
}
