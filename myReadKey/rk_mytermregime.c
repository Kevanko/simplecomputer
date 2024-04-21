#include <myReadKey.h>

// Функция, переключающая режим работы терминала (канонический /
// неканонический)
int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios curr;
  tcgetattr (fileno (stdin), &curr);

  if (regime)
    curr.c_lflag |= ICANON;
  else
    {
      curr.c_lflag &= ~ICANON;
      sigint ? (curr.c_lflag |= ISIG) : (curr.c_lflag &= ~ISIG);
      echo ? (curr.c_lflag |= ECHO) : (curr.c_lflag &= ~ECHO);
      curr.c_cc[VMIN] = vmin;
      curr.c_cc[VTIME] = vtime;
    }

  tcsetattr (0, TCSAFLUSH, &curr);

  return 0;
}
