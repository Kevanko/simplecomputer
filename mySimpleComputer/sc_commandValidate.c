#include "../include/mySimpleComputer.h"

int
sc_commandValidate (int command)
{
  if (command < 0 || command > 127)
    return -1;
  return 0;
}
