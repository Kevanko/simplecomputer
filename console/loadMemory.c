#include "console.h"

int
loadMemory ()
{
  char filename[101];
  printf ("Enter load file name: ");
  fgets (filename, 101, stdin);
  mt_clrscr ();
  mt_gotoXY (0, 25);
  filename[strlen (filename) - 1] = '\0';
  if (sc_memoryLoad (filename))
    {
      printf ("\nFailed to load memory               ");
      return -1;
    }
  else
    {
      printf ("\nSuuccessful load memory             ");
    }
  return 0;
}