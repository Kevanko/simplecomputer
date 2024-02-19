#pragma once
#include <stdio.h>

// Определение размера команды в битах
#define COMMAND_SIZE 16

// Бит, указывающий на знак числа в команде
#define COMMAND_SIGN_BIT                                                      \
    0x8000 // Этот бит устанавливается в 1 для отрицательных чисел и 0 для
           // положительных

// Биты, хранящие номер команды в команде
#define COMMAND_COMMAND_BITS                                                  \
    0x7C00 // Эти биты содержат номер операции (команды)

#define COMMAND_COMMAND_SHIFT                                                 \
    10 // Сдвигает биты номера команды, чтобы получить целое число

// Биты, хранящие операнд в команде
#define COMMAND_OPERAND_BITS                                                  \
    0x03FF // Эти биты содержат операнд, с которым нужно выполнить операцию

// Определение размера памяти
#define MEMORY_SIZE 128
// Определение масок для регистров флагов

// Маска для флага переполнения
#define FLAG_OVERFLOW_MASK                                                    \
    0x01 // Бит, который указывает на переполнение числа после выполнения
         // операции
// Маска для флага нуля

#define FLAG_ZERO_MASK                                                        \
    0x02 // Бит, который указывает, равен ли результат операции нулю
// Маска для флага выхода за границы памяти

#define FLAG_OUT_OF_MEMORY_MASK                                               \
    0x04 // Бит, который указывает, вышел ли результат операции за границы
         // доступной памяти

// Определение констант для значений по умолчанию
#define DEFAULT_ACCUMULATOR_VALUE 0
#define DEFAULT_COUNTER_VALUE 0
#define DEFAULT_FLAGS_VALUE 0
// Функции кодирования и декодирования команды
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);

// Функция проверки корректности команды
int sc_commandValidate (int command);

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit ();
int sc_accumulatorInit ();
int sc_icounterInit ();

int sc_regSet (int reg, int value);
int sc_accumulatorSet (int value);
int sc_icounterSet (int value);

int sc_regGet (int reg, int *value);
int sc_accumulatorGet (int *value);
int sc_icounterGet (int *value);
