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
          mt_gotoXY (75, 20);
          printf("      ");
          printTerm(operand, 0);
          rk_mytermrestore();
          mt_gotoXY (75, 20);
          if(rk_readvalue (&read, 0))
            read = 0;
          rk_mytermregime (0, 30, 0, 0, 0);

          inoutSet(operand, read);

          if (sc_memorySet (operand, read) != 0){
              sc_regSet (FLAG_IGNORE_CLOCK_MASK, 0);
              break;
          }
          sc_regSet (FLAG_IGNORE_CLOCK_MASK, 0);
          break;

        case WRITE:
          printTerm(operand, -1);
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
          if ((accumulator >> 14) & 1 && accumulator != 0)
            sc_icounterSet (operand - 1);
          break;

        case JZ:
          if (accumulator == 0)
            sc_icounterSet (operand - 1);
          break;

        case JNS: // Дополнительное
          if ((!(accumulator >> 14) & 1) && accumulator != 0)
            sc_icounterSet (operand - 1);
          break;

        case HALT:
          sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
          break;

        default:
          sc_regSet (FLAG_IGNORE_CLOCK_MASK, 1);
          break;
        }
    }
  instruction_counter ++;
}