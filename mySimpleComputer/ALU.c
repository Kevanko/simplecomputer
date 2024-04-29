#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "stdio.h"

int
ALU (int command, int operand)
{
  switch (command)
    {
    case ADD:
      accumulator += memory[operand];
      break;

    case SUB:
      accumulator -= memory[operand];
      break;

    case DIVIDE:
      if (memory[operand] != 0)
        accumulator /= memory[operand];
      else
        {
          sc_regSet (FLAG_DIVISION_BY_ZERO_MASK, 1);
          return -1;
        }
      break;

    case MUL:
      accumulator *= memory[operand];
      break;

    case CHL: // Дополнительное
      accumulator = memory[operand] << 1;
      break;
    }
  if ((accumulator > 0x3FFF) || (accumulator < 0))
    {
      sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
      return -1;
    }
  else
    sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 0);

  return 0;
}