#include <myReadKey.h>

/// Возвращающую первую клавишу, которую нажал пользователь
int
rk_readkey (enum keys *key)
{
  fflush (stdout); // очистка потока вывода
  char buffer[5] = "\0";
  rk_mytermregime (0, 30, 0, 0, 0);
  read (fileno (stdin), buffer, 5);
  rk_mytermrestore ();
  if (key == NULL)
    return 0;
  if (buffer[0] == '\033')
    if (buffer[1] == '\0')
      *key = KEY_ESC;
    else if (buffer[1] == '[')
      if (buffer[2] == 'A' && buffer[3] == '\0')
        *key = KEY_UP;
      else if (buffer[2] == 'B' && buffer[3] == '\0')
        *key = KEY_DOWN;
      else if (buffer[2] == 'C' && buffer[3] == '\0')
        *key = KEY_RIGHT;
      else if (buffer[2] == 'D' && buffer[3] == '\0')
        *key = KEY_LEFT;
      else if (buffer[2] == '1' && buffer[3] == '5')
        *key = KEY_F5;
      else if (buffer[2] == '1' && buffer[3] == '7')
        *key = KEY_F6;
      else
        *key = KEY_OTHER;
    else
      *key = KEY_OTHER;
  else if (buffer[0] == '\n' && buffer[1] == '\0')
    *key = KEY_ENTER;
  else if ((buffer[0] == 'l' || buffer[0] == 'L') && buffer[1] == '\0')
    *key = KEY_L;
  else if ((buffer[0] == 's' || buffer[0] == 'S') && buffer[1] == '\0')
    *key = KEY_S;
  else if ((buffer[0] == 'r' || buffer[0] == 'R') && buffer[1] == '\0')
    *key = KEY_R;
  else if ((buffer[0] == 't' || buffer[0] == 'T') && buffer[1] == '\0')
    *key = KEY_T;
  else if ((buffer[0] == 'i' || buffer[0] == 'I') && buffer[1] == '\0')
    *key = KEY_I;

  else
    *key = KEY_OTHER;
  return 0;
}
