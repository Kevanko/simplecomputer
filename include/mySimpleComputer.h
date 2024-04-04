#pragma once

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define COMMAND_SIZE 15
#define COMMAND_SIGN_BIT 0x4000     //    1000000 00000000
#define COMMAND_COMMAND_BITS 0x3F80 //    0111111 10000000
#define COMMAND_COMMAND_SHIFT 7     // >> 0000000 01111111
#define COMMAND_OPERAND_BITS 0x007F //    0000000 01111111

#define MEMORY_SIZE 128

#define FLAG_OVERFLOW_MASK 0x1         // O
#define FLAG_DIVISION_BY_ZERO_MASK 0x2 // Z
#define FLAG_OUT_OF_MEMORY_MASK 0x4    // M
#define FLAG_INVALID_COMMAND_MASK 0x8  // E
#define FLAG_IGNORE_CLOCK_MASK 0x10    // T

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