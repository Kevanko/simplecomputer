#pragma once
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>

#define MEMORY_X 2
#define MEMORY_Y 2

#define ACCUMULATOR_X 66
#define ACCUMULATOR_Y 2

#define FLAGS_X 92
#define FLAGS_Y 2

#define INSTR_COUNTER_X 67
#define INSTR_COUNTER_Y 5

#define COMMAND_X 96
#define COMMAND_Y 5

#define DECODE_X 3
#define DECODE_Y 17

#define EDITED_CELL_X 2
#define EDITED_CELL_Y 20

#define INOUT_BLOCK_X 69
#define INOUT_BLOCK_Y 20
#define INOUT_BLOCK_HEIGHT 4

#define FONT_SIZE 18
#define CHAR_SIZE 2

extern int ACTIVE_MEMORY;
extern int INOUT_ARRAY[];
extern int INOUT_INPUT[];
extern int font[FONT_SIZE][CHAR_SIZE];

void printCell (int address, enum colors fg, enum colors bg);
void printFlags ();
void printDecodedCommand (int value);
void printAccumulator ();
void printCounters ();
void printCommand ();
void printMemory ();
void printTerm (int address, int input);
void moveInout ();
int generateFont ();
void printBigCell (int cell, int x, int y);
void editCell (int *cell);
void handleKeypress (enum keys *key);
int checkConsole (int argv, char *argc[]);
void drawConsole ();
int loadMemory ();
int saveMemory ();
int setCellValue ();
int setCounterValue ();
int setAccumulatorValue ();
int setDefaultValue();