#include <myReadKey.h>
// Функция, сохраняющая текущие параметры терминала
int
rk_mytermsave ()
{
  if (tcgetattr (fileno (stdin), &SETTINGS))
    return -1;
  return 0;
}