#include <myReadKey.h>

// Функция, восстанавливающая сохраненные параметры терминала
int
rk_mytermrestore ()
{
  tcsetattr (fileno (stdin), TCSAFLUSH, &SETTINGS);
  return 0;
}
