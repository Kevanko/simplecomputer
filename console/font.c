#include "console.h"

int
generateFont ()
{
  FILE *file;
  int default_font[FONT_SIZE][CHAR_SIZE] = {
    { 0xC3C3C3FF, 0xFFC3C3C3 }, // 0
    { 0x18181C18, 0xFF181818 }, // 1
    { 0xFFC0C0FF, 0xFF030303 }, // 2
    { 0xFEC0C0FF, 0xFFC0C0FE }, // 3
    { 0xFFC3C3C3, 0xC0C0C0C0 }, // 4
    { 0xFF0303FF, 0xFFC0C0C0 }, // 5
    { 0xFF0303FF, 0xFFC3C3C3 }, // 6
    { 0x3030C0FF, 0x0C0C0C30 }, // 7
    { 0xFFC3C3FF, 0xFFC3C3FF }, // 8
    { 0xFFC3C3FF, 0xFFC0C0C0 }, // 9
    { 0xC3C3C3FF, 0xC3C3C3FF }, // a
    { 0xC3C3C37F, 0x7FC3C37F }, // b
    { 0x030303FF, 0xFF030303 }, // c
    { 0xC3C3C33F, 0x3FC3C3C3 }, // d
    { 0xFF0303FF, 0xFF0303FF }, // e
    { 0xFF0303FF, 0x030303FF }, // f
    { 0xFF181800, 0x001818FF }, // +
    { 0x18181C18, 0x18181818 }  // 1
  };
  // Открытие файла для записи
  file = fopen ("font.bin", "wb");
  if (file == NULL)
    {
      printf ("Ошибка открытия файла\n");
      return 1;
    }

  // Запись шрифта в файл
  int fd = fileno (file); // Получаем файловый дескриптор
  bc_bigcharwrite (fd, (int *)default_font, FONT_SIZE);
  fclose (file);

  return 0;
}
