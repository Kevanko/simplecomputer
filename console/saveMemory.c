#include "console.h"

int
saveMemory ()
{
  char filename[101];
  printf ("Enter save file name: ");
  fgets (filename, 101, stdin);
  mt_clrscr ();
  mt_gotoXY (0, 26);
  filename[strlen (filename) - 1] = '\0';

  if (sc_memorySave (filename))
    {
      printf ("\nFailed to save memory                         ");
      return -1;
    }
  else
    {
      printf ("\nSuuccessful saving memory                     ");
    }
  return 0;
}