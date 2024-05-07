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
#define CACHE_LINES 5      // Количество строк в кэше
#define CACHE_LINE_SIZE 10 // Размер строки кэша (10 ячеек)

#define FLAG_OVERFLOW_MASK 0x1         // O
#define FLAG_DIVISION_BY_ZERO_MASK 0x2 // Z
#define FLAG_OUT_OF_MEMORY_MASK 0x4    // M
#define FLAG_INVALID_COMMAND_MASK 0x8  // E
#define FLAG_IGNORE_CLOCK_MASK 0x10    // T

extern int *memory;
extern int accumulator;
extern int instruction_counter;
extern int flags_register;
extern int TACTS;

typedef struct CACHE
{
  int c_line[CACHE_LINE_SIZE];
  int c_number;
  int c_uses;
} CACHE;

extern CACHE cache[CACHE_LINES];

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
void CU ();
int ALU (int command, int operand);
void IRC (int signum);
int cacheCheck (int instruction);
void cacheLoad (CACHE *changed);

#pragma once
//Операции ввода/вывода
#define READ 0x10
#define WRITE 0x11

//Операции загрузки/выгрузки в аккумулятор
#define LOAD 0x20
#define STORE 0x21

//Арифметические операции
#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33

//Операции передачи управления
#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43

// Пользовательские функции
#define JNS 0x55
#define CHL 0x60
