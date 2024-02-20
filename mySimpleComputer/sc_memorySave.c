#include <mySimpleComputer.h>

extern int memory;

int
sc_memorySave (char *filename)
{
  if (!filename)
    {
      return -1; // неверный указатель на имя файла
    }
  FILE *file = fopen (filename, "wb");
  if (!file)
    {
      return -1; // ошибка открытия файла
    }
  fwrite (memory, sizeof (int), MEMORY_SIZE, file);
  fclose (file);
  return 0;
}