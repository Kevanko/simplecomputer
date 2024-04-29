#include "console.h"

void
handleKeypress (enum keys *key)
{
  switch (*key)
    {
    case KEY_R:
      sc_regSet (FLAG_IGNORE_CLOCK_MASK, 0);
      interact_mode = 1;
      break;
    case KEY_T:
      if (instruction_counter >= 127)
        instruction_counter = 0;
      else if (interact_mode)
        CU ();
      break;
    case KEY_I:
      raise (SIGUSR1);
      break;
    }

  if (interact_mode)
    return;

  switch (*key)
    {
    case KEY_UP:
      (instruction_counter <= 9)
          ? (instruction_counter += (instruction_counter >= 8 ? 110 : 120))
          : (instruction_counter -= 10);
      break;
    case KEY_RIGHT:
      (!((instruction_counter + 1) % (instruction_counter >= 120 ? 8 : 10)))
          ? (instruction_counter -= (instruction_counter >= 120 ? 7 : 9))
          : (instruction_counter += 1);
      break;
    case KEY_DOWN:
      (instruction_counter >= 118)
          ? (instruction_counter -= (instruction_counter < 120 ? 110 : 120))
          : (instruction_counter += 10);
      break;
    case KEY_LEFT:
      (!(instruction_counter % 10))
          ? (instruction_counter += (instruction_counter >= 120 ? 7 : 9))
          : (instruction_counter -= 1);
      break;

    case KEY_L:
      loadMemory ();
      break;
    case KEY_S:
      saveMemory ();
      break;

    case KEY_F5:
      setAccumulatorValue ();
      break;
    case KEY_F6:
      setCounterValue ();
      break;

    case KEY_ENTER:
      setCellValue ();
      break;

    case KEY_OTHER:
      break;

    case KEY_ESC:
      break;
    }
}
