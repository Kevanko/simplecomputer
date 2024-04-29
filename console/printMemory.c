#include "console.h"

void
printMemory ()
{
  enum colors fg = GREEN, bg = BLACK;
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      if (i == instruction_counter)
        {
          fg = BLACK;
          bg = WHITE;
        }
      else
        {
          fg = GREEN;
          bg = BLACK;
        }
      printCell (i, fg, bg);
    }
}