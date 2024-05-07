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
      accumulator = (accumulator + memory[operand]) & 0x7FFF;
      break;

    case SUB:
      accumulator = (accumulator + ~memory[operand] + 1) & 0x7FFF;
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
      accumulator = (accumulator * memory[operand]) & 0x7FFF;
      break;

    case CHL: // Дополнительное
      accumulator = (memory[operand] << 1) & 0x7FFF;
      break;
    }
  if ((accumulator > 0x7FFF) || (accumulator < 0))
    {
      sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
      return -1;
    }
  else
    sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 0);

  return 0;
}