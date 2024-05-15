#include "rpm.h"
#include <stdio.h>
#include <stdlib.h> // Добавлен заголовок для функции exit()
#include <string.h>

#define MEM_SIZE 128

// Операции ввода/вывода
#define READ 0x10
#define WRITE 0x11
// Операции загрузки/выгрузки в аккумулятор
#define LOAD 0x20
#define STORE 0x21
// Арифметические операции
#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33
// Операции передачи управления
#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43
// Пользовательские функции
#define JNS 0x55
#define CHL 0x60

typedef struct VARIABLES
{
  char name[2];
  int value;
  int address;
} VARIABLES;

typedef struct MEMORY
{
  int command;
  int operation;
  VARIABLES *var;
  int id;
} MEMORY;

MEMORY memory[MEM_SIZE];
VARIABLES vars[MEM_SIZE];
VARIABLES empty_var = { 0 };

int memory_next = 0; // Инициализация переменной memory_next
int vars_next = 0; // Инициализация переменной vars_next

int
checkVar (char *var)
{
  int count_numb = 0; // Инициализация переменной count_numb
  for (int i = 0; i < strlen (var); i++)
    {
      if ((var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && var[i] <= 'z'))
        { // Изменены условия проверки
          if (i > 0)
            return -1;
        }
      else if (var[i] >= '0' && var[i] <= '9')
        {
          count_numb++;
        }
      else
        {
          return -1;
        }
    }
  if (count_numb == strlen (var))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int
get_id (int id)
{
  for (int i = 0; i < memory_next; i++)
    { // Исправлен цикл на memory_next
      if (memory[i].id == id)
        {
          return i;
        }
    }
  return -1;
}

int
get_var_by_name (char *ch)
{
  for (int i = 0; i < vars_next; i++)
    {
      if (strcmp (vars[i].name, ch) == 0)
        { // Изменено сравнение на strcmp()
          return i;
        }
    }
  return -1;
}

VARIABLES *
set_var_memory (char *var_name)
{
  int var_id = get_var_by_name (var_name);
  if (var_id == -1)
    {
      strcpy (vars[vars_next].name, var_name);
      vars[vars_next].address = -1;
      vars[vars_next].value = 0;
      return &vars[vars_next++];
    }
  else
    {
      return &vars[var_id];
    }
}

void
memory_set (int id, int command, VARIABLES *var)
{
  memory[memory_next].id = id;
  memory[memory_next].operation = command;
  memory[memory_next].var = var;
  memory_next++;
}

void
let_func (char *buff, int id, int *deeps, VARIABLES *var, int is_load,
          int operation)
{
  char name[2];
  name[1] = '\0';
  if (isalpha (buff[*deeps - 1]))
    {
      memory_next++;
      name[0] = buff[--*deeps];
      var = set_var_memory (name);
      memory_set (id, operation, var);
      memory_next -= 2;
      name[0] = buff[--*deeps];
      var = set_var_memory (name);
      if (!is_load)
        {
          memory_set (id, LOAD, var);
          is_load = 1;
        }
      else
        memory_set (id, operation, var);
      memory_next++;
      *deeps--;
    }
  else
    {

      int counter = 1, num = 0;
      while (isdigit (buff[*deeps - 1]))
        {
          num += (buff[--*deeps] - '0') * counter;
          counter *= 10;
        }
      char tname[2];
      sprintf (tname, "A%d", vars_next);
      var = set_var_memory (tname);
      var->value = num;
      memory_next++;
      memory_set (id, operation, var);
      memory_next -= 2;
      name[0] = buff[--*deeps];
      var = set_var_memory (name);
      if (!is_load)
        {
          memory_set (id, LOAD, var);
          is_load = 1;
        }
      else
        memory_set (id, operation, var);
      memory_next++;
      *deeps--;
    }
}

int
get_command (int id, char *command, char *line)
{
  char var_name[2]; // Изменен размер массива var_name
  VARIABLES *var;
  if (strcmp (command, "REM") == 0)
    {
      return 0;
    }
  else if (strcmp (command, "INPUT") == 0)
    {
      char s[100];
      sscanf (line, "%*s %s", var_name);
      var = set_var_memory (var_name);
      memory_set (id, READ, var);
      translate_to_rpn (s, strstr (line, var_name));
    }
  else if (strcmp (command, "IF") == 0)
    {
      char operand[2];
      char newCommand[10];
      sscanf (line, "%*s %s %s %*d %s", var_name, operand, newCommand);
      var = set_var_memory (var_name);
      memory_set (id, LOAD, var);
      if (strlen (operand) == 1)
        {
          switch (operand[0])
            {
            case '<':
              memory[memory_next].operation = JNEG;
              break;
            case '>':
              memory[memory_next].operation = JNS;
              break;
            case '=':
              memory[memory_next].operation = JUMP;

              break;
            default:
              return 0;
            }
        }
      else
        {
          return 0;
        }
      memory[memory_next].id = id;
      memory[memory_next].var = &empty_var;
      memory[memory_next].command
          = (memory[memory_next].operation << 7) + memory_next + 2;
      memory_next++;
      int temp_mem = memory_next;
      memory_set (id, JUMP, &empty_var);
      get_command (id, newCommand, strstr (line, newCommand));

      memory[temp_mem].command
          = (memory[temp_mem].operation << 7) + memory_next;
      return 1;
    }
  else if (strcmp (command, "PRINT") == 0)
    {
      sscanf (line, "%*s %s", var_name);
      var = set_var_memory (var_name);
      memory_set (id, WRITE, var);
    }
  else if (strcmp (command, "LET") == 0)
    {
      char s[100];
      sscanf (line, "%*s %s", var_name);
      translate_to_rpn (s, strstr (line, "=") + 1);
      char buff[60];
      int num = 0, n = 0;
      int deeps = 0;
      int is_load = 0;
      while (s[n] != '\0')
        {
          if (isalpha (s[n]) || isdigit (s[n]))
            buff[deeps++] = s[n];
          if (s[n] == '+' || s[n] == '-' || s[n] == '/' || s[n] == '*')
            {
              switch (s[n])
                {
                case '+':
                  let_func (buff, id, &deeps, var, is_load, ADD);
                  break;
                case '-':
                  let_func (buff, id, &deeps, var, is_load, SUB);
                  break;
                case '/':
                  let_func (buff, id, &deeps, var, is_load, DIVIDE);
                  break;
                case '*':
                  let_func (buff, id, &deeps, var, is_load, MUL);
                  break;
                default:
                  break;
                }
            }
          n++;
        }
      is_load = 0;
      char name[2];
      name[1] = '\0';
      if (deeps > 0)
        {
          if (isalpha (buff[deeps - 1]))
            {
              name[0] = buff[--deeps];
              var = set_var_memory (name);
              memory_set (id, LOAD, var);
              deeps = 0;
            }
          else
            {
              int counter = 1;
              while (deeps > 0)
                {
                  num += (buff[--deeps] - '0') * counter;
                  counter *= 10;
                }
              char tname[5];
              sprintf (tname, "A%d", vars_next);
              var = set_var_memory (tname);
              memory_set (id, LOAD, var);
              var->value = num;
            }
        }

      var = set_var_memory (var_name);
      memory_set (id, STORE, var);
    }

  else if (strcmp (command, "GOTO") == 0)
    {
      int goto_id;
      sscanf (line, "%*s %d", &goto_id);
      memory_set (id, (JUMP << 7) + goto_id, &empty_var);
    }
  else if (strcmp (command, "END") == 0)
    {
      memory_set (id, HALT, &empty_var);
    }
  else
    {
      return 0;
    }
  return 1;
}

void
set_var_addr ()
{
  for (int i = 0; i < vars_next; i++)
    {
      vars[i].address = memory_next;
      memory[memory_next].command = vars[i].value;
      memory[memory_next].var = &vars[i];
      memory_next++;
    }
}

void
set_commands ()
{
  for (int i = 0; i < memory_next; i++)
    {
      if (memory[i].command == 0 && memory[i].operation != 0
          && (memory[i].operation >> 7) != JUMP && memory[i].var)
        {
          memory[i].command
              = (memory[i].operation << 7) + memory[i].var->address;
        }
    }
}

void
set_gotos ()
{
  for (int i = 0; i < memory_next; i++)
    {
      if ((memory[i].operation >> 7) == JUMP && memory[i].command == 0)
        {
          int tmp = memory[i].operation & 0x7F;
          int JUMPid = get_id (tmp);
          memory[i].operation = (memory[i].operation >> 7) & 0x7F;
          memory[i].command = (memory[i].operation << 7) + JUMPid;
        }
    }
}

void
READinstructions (const char *filename)
{
  FILE *file = fopen (filename, "r");
  if (file == NULL)
    {
      printf ("Error opening file.\n");
      exit (EXIT_FAILURE);
    }

  int id = 0;
  char *line = NULL;
  size_t len = 0;
  char command[10];
  while (getline (&line, &len, file) != -1)
    {
      if (sscanf (line, "%d %s", &id, command) == 2)
        {
          if (get_command (id, command, strstr (line, command)))
            {
              // printf ("%d %s\n", id, command);
            }
        }
      else
        {
          printf ("ERROR\n");
        }
    }
  set_var_addr ();
  set_commands ();
  set_gotos ();
  fclose (file);
}

char *
get_command_text (int command)
{
  if (command == READ)
    return "READ";
  else if (command == WRITE)
    return "WRITE";
  else if (command == LOAD)
    return "LOAD";
  else if (command == STORE)
    return "STORE";
  else if (command == ADD)
    return "ADD";
  else if (command == SUB)
    return "SUB";
  else if (command == DIVIDE)
    return "DIVIDE";
  else if (command == MUL)
    return "MUL";
  else if (command == JUMP)
    return "JUMP";
  else if (command == JNEG)
    return "JNEG";
  else if (command == JZ)
    return "JZ";
  else if (command == JNS)
    return "JNS";
  else if (command == CHL)
    return "CHL";
  else if (command == HALT)
    return "HALT";
  else
    return 0;
}

void
print_mem ()
{
  for (int i = 0; i < memory_next; i++)
    {
      if (memory[i].id != 0)
        printf ("[%d] %2.2d %s %2.2d\n", memory[i].id, i,
                get_command_text (memory[i].operation),
                memory[i].command & 0x7F);
      else
        printf ("[%2.2s] %2.2d = %04d -> VAR\n", memory[i].var->name, i,
                memory[i].command);
    }
}

void
save_mem (char *filename)
{
  printf ("%s\n", filename);
  FILE *f = fopen (filename, "w");
  for (int i = 0; i < memory_next; i++)
    {
      if (memory[i].id != 0)
        fprintf (f, "%2.2d %s %2.2d\n", i,
                 get_command_text (memory[i].operation),
                 memory[i].command & 0x7F);
      else
        fprintf (f, "%2.2d = %04d\n", i, memory[i].command);
    }
  fclose (f);
}

int
main (int argc, char *argv[])
{
  if (argc != 3)
    {
      printf ("Usage: %s filename.sb filename.sa \n", argv[0]);
      return EXIT_FAILURE;
    }

  READinstructions (argv[1]);
  // print_mem ();
  save_mem (argv[2]);
  return EXIT_SUCCESS;
}
