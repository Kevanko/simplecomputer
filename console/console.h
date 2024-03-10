#pragma once
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>


#define MEMORY_X 2
#define MEMORY_Y 2

#define ACCUMULATOR_X 91
#define ACCUMULATOR_Y 2

#define FLAGS_X 121
#define FLAGS_Y 2

#define INSTR_COUNTER_X 91
#define INSTR_COUNTER_Y 4

#define COMMAND_X 2
#define COMMAND_Y 16

#define EDITED_CELL_X 2
#define EDITED_CELL_Y 20

#define INOUT_BLOCK_X 91
#define INOUT_BLOCK_Y 8
#define INOUT_BLOCK_HEIGHT 4

void printCell (int address, enum colors fg, enum colors bg);
void printFlags ();
void printDecodedCommand (int value);
void printAccumulator ();
void printCounters ();