#include <mySimpleComputer.h>

int *memory;
int accumulator;
int instruction_counter;
int flags_register;
int TACTS = 0;

CACHE cache[CACHE_LINES] = {{0}, 0, 0};
