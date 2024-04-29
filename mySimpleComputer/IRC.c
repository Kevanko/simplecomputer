#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "signal.h"
#include "stdio.h"

void
IRC (int signum)
{
  if (signum == SIGALRM)
    {
      int flagt;
      sc_regGet (FLAG_IGNORE_CLOCK_MASK, &flagt);
      fflush (stdout);
      if (!flagt)
        {
          CU ();
        }
    }
  else if (signum == SIGUSR1)
    {
      sc_accumulatorSet (0);
      printAccumulator ();
      for (int i = 0; i < 128; i++)
        {
          if (sc_memorySet (i, 0) != 0)
            return -1;
        }
      sc_icounterSet (0);
    }
}