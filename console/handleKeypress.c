#include "console.h"

void
handleKeypress (enum keys *key)
{
  switch (*key)
    {
    case KEY_UP:
      (ACTIVE_MEMORY <= 9)
          ? (ACTIVE_MEMORY += (ACTIVE_MEMORY >= 8 ? 110 : 120))
          : (ACTIVE_MEMORY -= 10);
      break;
    case KEY_RIGHT:
      (!((ACTIVE_MEMORY + 1) % (ACTIVE_MEMORY >= 120 ? 8 : 10)))
          ? (ACTIVE_MEMORY -= (ACTIVE_MEMORY >= 120 ? 7 : 9))
          : (ACTIVE_MEMORY += 1);
      break;
    case KEY_DOWN:
      (ACTIVE_MEMORY >= 118)
          ? (ACTIVE_MEMORY -= (ACTIVE_MEMORY < 120 ? 110 : 120))
          : (ACTIVE_MEMORY += 10);
      break;
    case KEY_LEFT:
      (!(ACTIVE_MEMORY % 10))
          ? (ACTIVE_MEMORY += (ACTIVE_MEMORY >= 120 ? 7 : 9))
          : (ACTIVE_MEMORY -= 1);
      break;

    case KEY_L:
      loadMemory ();
      break;
    case KEY_S:
      saveMemory ();
      break;

    case KEY_R:
      break;
    case KEY_T:
      break;
    case KEY_I:
      setDefaultValue ();
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
