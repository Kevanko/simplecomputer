#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define COMMAND_SIZE 16
#define COMMAND_SIGN_BIT 0x8000      //  10000000 00000000
#define COMMAND_COMMAND_BITS 0x7C00  //  01111100 00000000
#define COMMAND_COMMAND_SHIFT 10     //>>00000000 00011111
#define COMMAND_OPERAND_BITS 0x03FF  //  00000011 11111111
#define FLAG_OVERFLOW_MASK 0x01      //                001
#define FLAG_ZERO_MASK 0x02          //                010
#define FLAG_OUT_OF_MEMORY_MASK 0x04 //                100

#define MEMORY_SIZE 128

extern int *memory;
extern int accumulator;
extern int instruction_counter;
extern int flags_register;

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);
void printCell (int address);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);