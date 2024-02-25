#include <mySimpleComputer.h>

int
sc_memoryLoad (char *filename)
{
  if (!filename)
    {
      return -1; // неверный указатель на имя файла
    }
  FILE *file = fopen (filename, "rb");
  if (!file)
    {
      return -1; // ошибка открытия файла
    }
  int buffer[MEMORY_SIZE];
  if (fread (buffer, sizeof (int), MEMORY_SIZE, file) == 0)
    return -1;
  fclose (file);
  // Если чтение успешно, переносим содержимое в оперативную память
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = buffer[i];
    }
  return 0;
}