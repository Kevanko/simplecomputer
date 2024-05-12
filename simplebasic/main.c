#include <stdio.h>
#include <stdlib.h> // Добавлен заголовок для функции exit()
#include <string.h>

#define MEM_SIZE 128

// Операции ввода/вывода
#define READ_ 0x10
#define WRITE_ 0x11
// Операции загрузки/выгрузки в аккумулятор
#define LOAD_ 0x20
#define STORE_ 0x21
// Арифметические операции
#define ADD_ 0x30
#define SUB_ 0x31
#define DIVIDE_ 0x32
#define MUL_ 0x33
// Операции передачи управления
#define JUMP_ 0x40
#define JNEG_ 0x41
#define JZ_ 0x42
#define HALT_ 0x43
// Пользовательские функции
#define JNS_ 0x55
#define CHL_ 0x60

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
VARIABLES empty_var = {0};

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

void
goto_command (int goto_id)
{
  memory[memory_next].operation = (JUMP_ << 7) + goto_id;
}

void
print_command ()
{
  memory[memory_next].operation = WRITE_;
}

void
input_command ()
{ // Переименована функция imput_command() на input_command()
  memory[memory_next].operation = READ_;
}

void
set_var_memory (char *var_name)
{
  int var_id = get_var_by_name (var_name);
  if (var_id == -1)
    {
      strcpy (vars[vars_next].name, var_name);
      vars[vars_next].address = -1;
      vars[vars_next].value = 0;
      memory[memory_next].var = &vars[vars_next];
      vars_next++;
    }
  else
    {
      memory[memory_next].var = &vars[var_id];
    }
}

 
void memory_set(int id, int command, VARIABLES *var){
      memory[memory_next].id = id;
    memory[memory_next].operation = command;
        memory[memory_next].var = var;
}
int
get_command (int id, char *command, char *line)
{
  char var_name[2]; // Изменен размер массива var_name
  if (strcmp (command, "REM") == 0)
    {
      return 0;
    }
  else if (strcmp (command, "INPUT") == 0)
    {
      sscanf (line, "%*s %s", var_name);
      set_var_memory (var_name);
      input_command ();
      memory[memory_next].id = id;
    }
  else if (strcmp (command, "IF") == 0)
    {
      char operand[2]; // Увеличил размер массива operand
      char newCommand[10];
      sscanf (line, "%*s %s %s %*d %s", var_name, operand, newCommand);
      set_var_memory (var_name);
      memory[memory_next].operation = LOAD_;
      memory[memory_next].id = id;
      memory_next++;
      int temp_mem = memory_next;
      if (strlen (operand) == 1)
        { // Проверяем, является ли оператор одним символом
          switch (operand[0])
            {
            case '<':
              memory[memory_next].operation = JNEG_;
              break;
            case '>':
              memory[memory_next].operation = JNS_;
              break;
            case '=':
              memory[memory_next].operation = JUMP_;
              break;
            default:
              return 0;
            }
        }
      else if (strlen (operand) == 2)
        { // Проверяем, является ли оператор двумя символами
          if (strcmp (operand, "<=") == 0)
            {
              memory[memory_next].operation = JNEG_;
            }
          else if (strcmp (operand, ">=") == 0)
            {
              memory[memory_next].operation = JNS_;
            }
          else if (strcmp (operand, "==") == 0)
            {
              memory[memory_next].operation = JUMP_;
            }
          else
            {
              return 0; // Неизвестный оператор
            }
        }
      else
        {
          return 0; // Оператор не является одним или двумя символами
        }
      memory[memory_next].id = id;
      memory[memory_next].var = &empty_var;
      memory_next++;
      get_command(id, newCommand, strstr(line, newCommand));

      memory[temp_mem].command
          = (memory[temp_mem].operation << 7) + memory_next;
      return 1;
    }
  else if (strcmp (command, "PRINT") == 0)
    {
      sscanf (line, "%*s %s", var_name);
      set_var_memory (var_name);
      print_command ();
      memory[memory_next].id = id;
    }
  else if (strcmp (command, "LET") == 0)
    {
      char *p = strtok (line, " "); // Разделитель - пробел
      p = strtok (NULL, " "); // Пропускаем LET
      sscanf (p, "%s", var_name); // Считываем имя переменной
      set_var_memory (var_name);
      memory[memory_next].id = id;
      memory[memory_next].operation = STORE_;
    }
  else if (strcmp (command, "GOTO") == 0)
    {
      int goto_id;
      sscanf (line, "%*s %d", &goto_id);
      memory[memory_next].id = id;
      memory[memory_next].var = &empty_var;
      goto_command (goto_id);
    }
  else if (strcmp (command, "END") == 0)
    {
      memory[memory_next].id = id;
      memory[memory_next].var = &empty_var;
      memory[memory_next].command = HALT_ << 7;
      memory[memory_next].operation = HALT_;
    }
  else
    {
      return 0;
    }
  memory_next++;
  return 1;
}

void
set_var_addr ()
{
  for (int i = 0; i < vars_next; i++)
    {
      vars[i].address = memory_next;
      memory[memory_next].command = vars[i].value;
      memory[memory_next].var = &empty_var;
      memory_next++;
    }
}

void
set_commands ()
{
  for (int i = 0; i < memory_next; i++)
    { // Изменен цикл на memory_next
      if (memory[i].command == 0 && memory[i].operation != 0
          && (memory[i].operation >> 7) != JUMP_ && memory[i].var)
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
    { // Изменен цикл на memory_next
      if ((memory[i].operation >> 7) == JUMP_ && memory[i].command == 0)
        {
          int tmp = memory[i].operation & 0x7F;
          int jump_id = get_id (tmp);
          memory[i].operation = (memory[i].operation >> 7) & 0x7F;
          memory[i].command = (memory[i].operation << 7) + jump_id;
        }
    }
}

void
read_instructions (const char *filename)
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
          if (get_command (id, command, strstr(line, command)))
            {
              printf ("%d %s\n", id, command);
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
  if (command == READ_)
    return "READ";
  else if (command == WRITE_)
    return "WRITE";
  else if (command == LOAD_)
    return "LOAD";
  else if (command == STORE_)
    return "STORE";
  else if (command == ADD_)
    return "ADD";
  else if (command == SUB_)
    return "SUB";
  else if (command == DIVIDE_)
    return "DIVIDE";
  else if (command == MUL_)
    return "MUL";
  else if (command == JUMP_ )
    return "JUMP";
  else if (command == JNEG_ )
    return "JNEG";
  else if (command == JZ_ )
    return "JZ";
  else if (command == JNS_ )
    return "JNS";
  else if (command == CHL_ )
    return "CHL";
  else if (command == HALT_)
    return "HALT";
  else
    return 0;
}

void print_mem(){
 for (int i = 0; i < memory_next; i++){
  if(memory[i].id != 0)
    printf("[%d] %2.2d %s %2.2d\n", memory[i].id, i, get_command_text(memory[i].operation), memory[i].command & 0x7F);
  else
      printf("     %2.2d = %04x\n", i, memory[i].command);
 }
}

int
main (int argc, char *argv[])
{
  if (argc != 2)
    {
      printf ("Usage: %s filename\n", argv[0]);
      return EXIT_FAILURE;
    }

  read_instructions (argv[1]);

  for (int i = 0; i < MEM_SIZE; i++)
    {
      printf ("%04X ", memory[i].command);
      if ((i + 1) % 10 == 0)
        {
          printf ("\n");
        }
    }
  printf ("\n");
  print_mem();
  return EXIT_SUCCESS; 
}
