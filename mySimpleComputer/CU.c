#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "stdio.h"

void
CU ()
{
  int operand, read, sign, command;
  if (sc_commandDecode (memory[instruction_counter], &sign, &command, &operand)
      != 0)
    {
      sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
      return;
    }
  if ((operand < 0) && (operand >= MEMORY_SIZE))
    {
      sc_regSet (FLAG_INVALID_COMMAND_MASK, 1);
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
      return;
    }
  if (command == ADD || command == SUB || command == DIVIDE || command == MUL
      || command == CHL)
    {
      if (ALU (command, operand) != 0)
        sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
    }
  else
    {
      switch (command)
        {
        case READ:
          mt_gotoXY (21, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (22, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (23, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (21, 123);
          printf ("Запись memory:");
          fflush (stdout);
          mt_gotoXY (22, 123);
          rk_readvalue (&read, 4);
          if (sc_memorySet (operand, read + 1280) != 0)
            {
              sc_regSet (FLAG_OUT_OF_MEMORY_MASK, 1);
              break;
            }
          break;

        case WRITE:
          mt_gotoXY (21, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (22, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (23, 123);
          printf ("             ");
          fflush (stdout);
          mt_gotoXY (21, 123);
          printf ("Вывод memory:");
          fflush (stdout);
          mt_gotoXY (22, 123);
          printf ("+%04x", memory[operand]);
          fflush (stdout);
          break;

        case LOAD:
          sc_accumulatorSet (memory[operand]);
          break;

        case STORE:
          sc_memorySet (operand, accumulator);
          break;

        case JUMP:
          sc_icounterSet (operand);
          break;

        case JNEG:
          if (accumulator < 0)
            sc_icounterSet (operand);
          break;

        case JZ:
          if (accumulator == 0)
            sc_icounterSet (operand);
          break;

        case JNS: // Дополнительное
          if (accumulator > 0)
            sc_icounterSet (operand);
          break;

        case HALT:
          sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
          break;

        default:
          sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
          break;
        }
    }
  instruction_counter++;
}