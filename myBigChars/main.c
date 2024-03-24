#include "myBigChars.h"
#include <ncurses.h>

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

int
bc_printA (char *str)
{
  printf ("\e(0%s\e(B", str);
  return 0;
}

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

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  int pos;

  if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
    return -1;

  if (y <= 3)
    pos = 0;
  else
    pos = 1;

  y = y % 4;

  if (value == 0)
    big[pos] &= ~(1 << (y * 8 + x));
  else
    big[pos] |= 1 << (y * 8 + x);

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int pos;

  if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
    return -1;

  if (y <= 3)
    pos = 0;
  else
    pos = 1;

  y = y % 4;
  *value = (big[pos] >> (y * 8 + x)) & 1;

  return 0;
}

int
bc_printbigchar (int *big, int x, int y, enum colors fg, enum colors bg)
{
  int maxx, maxy;
  int pos, bit;
  int i, j;
  char row[9];

  mt_getscreensize (&maxy, &maxx);
  if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
    return -1;
  row[8] = '\0';
  if (fg != BLACK)
    mt_setfgcolor (fg);
  if (bg != BLACK)
    mt_setbgcolor (bg);
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
        {
          pos = i >> 2;
          bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
          if (bit == 0)
            row[j] = ' ';
          else
            row[j] = BOXCHAR_REC;
        }
      mt_gotoXY (x, y + i);
      bc_printA (row);
    }

  mt_setdefaultcolor ();

  return 0;
}

int
bc_bigcharwrite (int fd, int *big, int count)
{
  int err;

  err = write (fd, &count, sizeof (count));
  if (err == -1)
    return -1;

  err = write (fd, big, count * (sizeof (int)) * 2);
  if (err == -1)
    return -1;

  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  int n, cnt, err;

  err = read (fd, &n, sizeof (n));
  if (err == -1 || (err != sizeof (n)))
    return -1;

  cnt = read (fd, big, need_count * sizeof (int) * 2);
  if (cnt == -1)
    return -1;

  *count = cnt / (sizeof (int) * 2);

  return 0;
}