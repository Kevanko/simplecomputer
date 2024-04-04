#include <myBigChars.h>

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  int tmp, maxx, maxy, header_len, header_pos;

  if (x1 > x2)
    {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
    }
  if (y1 > y2)
    {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
    }
  mt_getscreensize (&maxy, &maxx);
  if ((x1 < 0) || (y1 < 0) || (x2 > maxx) || (y2 > maxy) || (x2 - x1 < 2)
      || (y2 - y1 < 2))
    return -1;

  if (box_fg != 0)
    mt_setfgcolor (box_fg);
  if (box_bg != 0)
    mt_setbgcolor (box_bg);

  mt_gotoXY (x1, y1);
  bc_printA (BOXCHAR_TL);
  for (tmp = x1 + 1; tmp < x2; tmp++)
    bc_printA (BOXCHAR_HOR);
  bc_printA (BOXCHAR_TR);

  for (tmp = y1 + 1; tmp < y2; tmp++)
    {
      mt_gotoXY (x1, tmp);
      bc_printA (BOXCHAR_VERT);
      mt_gotoXY (x2, tmp);
      bc_printA (BOXCHAR_VERT);
    }

  mt_gotoXY (x1, y2);
  bc_printA (BOXCHAR_BL);
  for (tmp = x1 + 1; tmp < x2; tmp++)
    bc_printA (BOXCHAR_HOR);
  bc_printA (BOXCHAR_BR);

  if (header != NULL)
    {
      header_len = bc_strlen (header);
      header_pos = x1 + (x2 - x1) / 2 - header_len / 2;
      if (header_fg != 0)
        mt_setfgcolor (header_fg);
      if (header_bg != 0)
        mt_setbgcolor (header_bg);
      mt_gotoXY (header_pos, y1);
      printf (" %s ", header);
    }

  mt_setdefaultcolor ();

  return 0;
}