#include <mySimpleComputer.h>

int
sc_commandValidate (int command)
{
  // Извлекаем код операции из команды 
  int opCode = (command >> 7) & 0x7F;

  // Проверяем, является ли код операции допустимым
  if (opCode == 0x00 || // NOP
      opCode == 0x01 || // CPUINFO
      opCode == 0x0A || // READ
      opCode == 0x0B || // WRITE
      opCode == 0x14 || // LOAD
      opCode == 0x15 || // STORE
      opCode == 0x1E || // ADD
      opCode == 0x1F || // SUB
      opCode == 0x20 || // DIVIDE
      opCode == 0x21 || // MUL
      opCode == 0x28 || // JUMP
      opCode == 0x29 || // JNEG
      opCode == 0x2A || // JZ
      opCode == 0x2B || // HALT
      opCode == 0x33 || // NOT
      opCode == 0x34 || // AND
      opCode == 0x35 || // OR
      opCode == 0x36 || // XOR
      opCode == 0x37 || // JNS
      opCode == 0x38 || // JC
      opCode == 0x39 || // JNC
      opCode == 0x3A || // JP
      opCode == 0x3B || // JNP
      opCode == 0x3C || // CHL
      opCode == 0x3D || // SHR
      opCode == 0x3E || // RCL
      opCode == 0x3F || // RCR
      opCode == 0x40 || // NEG
      opCode == 0x41 || // ADDC
      opCode == 0x42 || // SUBC
      opCode == 0x43 || // LOGLC
      opCode == 0x44 || // LOGRC
      opCode == 0x45 || // RCCL
      opCode == 0x46 || // RCCR
      opCode == 0x47 || // MOVA
      opCode == 0x48 || // MOVR
      opCode == 0x49 || // MOVCА
      opCode == 0x4A || // MOVCR
      opCode == 0x4B || // ADDC
      opCode == 0x4C)   // SUBC
    {
      return 0; // Команда допустима
    }

  return -1; // Команда недопустима
}
