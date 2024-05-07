#include <stdio.h>
#include <string.h>
#define MEM_SIZE 128

//Операции ввода/вывода
#define READ_ 0x10
#define WRITE_ 0x11

//Операции загрузки/выгрузки в аккумулятор
#define LOAD_ 0x20
#define STORE_ 0x21

//Арифметические операции
#define ADD_ 0x30
#define SUB_ 0x31
#define DIVIDE_ 0x32
#define MUL_ 0x33

//Операции передачи управления
#define JUMP_ 0x40
#define JNEG_ 0x41
#define JZ_ 0x42
#define HALT_ 0x43

// Пользовательские функции
#define JNS_ 0x55
#define CHL_ 0x60

int memory[MEM_SIZE] = { 0 };

int
get_command (char *command)
{
  if (strcmp (command, "READ") == 0)
    return READ_;
  else if (strcmp (command, "WRITE") == 0)
    return WRITE_;
  else if (strcmp (command, "LOAD") == 0)
    return LOAD_;
  else if (strcmp (command, "STORE") == 0)
    return STORE_;
  else if (strcmp (command, "ADD") == 0)
    return ADD_;
  else if (strcmp (command, "SUB") == 0)
    return SUB_;
  else if (strcmp (command, "DIVIDE") == 0)
    return DIVIDE_;
  else if (strcmp (command, "MUL") == 0)
    return MUL_;
  else if (strcmp (command, "JUMP") == 0)
    return JUMP_;
  else if (strcmp (command, "JNEG") == 0)
    return JNEG_;
  else if (strcmp (command, "JZ") == 0)
    return JZ_;
  else if (strcmp (command, "JNS") == 0)
    return JNS_;
  else if (strcmp (command, "CHL") == 0)
    return CHL_;
  else if (strcmp (command, "HALT") == 0)
    return HALT_;
  else
    return 0;
}

void
read_instructions (const char *filename)
{
  FILE *file = fopen (filename, "r");
  if (file == NULL)
    {
      printf ("Error opening file.\n");
      return;
    }

  int address, value, i;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char command[10];
    while ((read = getline(&line, &len, file)) != -1)
    {
      if (sscanf (line, "%d %s %d", &address, &command, &value) == 3)
        {
          int cmd = get_command (command);
          memory[address] = value | cmd << 7;
          printf ("COOL: %d %s %d\n", address, command, value);
        }
      else
        {
          printf("ERROR\n");
        }
    }

  fclose (file);
}

int
main ()
{
  read_instructions ("instructions.sa");
  for (int i = 0; i < MEM_SIZE; i++)
    {
      printf ("%04x ", memory[i]);
      if ((i + 1) % 10 == 0)
        printf ("\n");
    }
  FILE *f = fopen ("result.o", "wb");
  fwrite (memory, sizeof (int), MEM_SIZE, f);
  printf ("\n");
  return 0;
}