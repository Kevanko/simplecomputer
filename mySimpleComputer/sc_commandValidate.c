#include <mySimpleComputer.h>

int
sc_commandValidate (int command)
{
  // Проверяем, является ли код операции допустимым
  if (command == 0x00 || command == 0x01 || command == READ || command == WRITE
      || command == LOAD || command == STORE || command == ADD
      || command == SUB || command == DIVIDE || command == MUL
      || command == JUMP || command == JNEG || command == JZ || command == HALT
      || command == CHL || command == JNS)
    {
      return 0;
    }

  return -1;
}
