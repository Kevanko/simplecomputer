#include <stdio.h>
#include <stdlib.h>

#define FONT_SIZE 18
#define CHAR_SIZE 2

int
generateFont ()
{
  FILE *file;
  int font[FONT_SIZE][CHAR_SIZE];
  int i, j, fontsize = FONT_SIZE;

  // Инициализация массива шрифта
  for (i = 0; i < FONT_SIZE; i++)
    {
      for (j = 0; j < CHAR_SIZE; j++)
        {
          font[i][j] = 0;
        }
    }

  // Задание значений символов шрифта
  font[0][0] = 0x818181FF;
  font[0][1] = 0xFF818181; // 0
  font[1][1] = 0x24242424; // 1
  font[2][0] = 0xE1A5A59A;
  font[2][1] = 0x8F8985A5; // 2
  font[3][0] = 0x1818187E;
  font[3][1] = 0x18181818; // 3
  font[4][0] = 0x464E5A71;
  font[4][1] = 0x00000000; // 4
  font[5][0] = 0x81818181;
  font[5][1] = 0x81818181; // 5
  font[6][0] = 0xC183858D;
  font[6][1] = 0x91A1C0C0; // 6
  font[7][0] = 0x0103060E;
  font[7][1] = 0x10101010; // 7
  font[8][0] = 0x8D929294;
  font[8][1] = 0x82848C90; // 8
  font[9][0] = 0x4646463C;
  font[9][1] = 0x46464646; // 9
  font[10][0] = 0x4242423C;
  font[10][1] = 0x42424242; // A
  font[11][0] = 0x6D9292FE;
  font[11][1] = 0xFE92926D; // B
  font[12][0] = 0x8181813C;
  font[12][1] = 0x3C818181; // C
  font[13][0] = 0xFE818181;
  font[13][1] = 0x818181FE; // D
  font[14][0] = 0x8181817E;
  font[14][1] = 0x7E818181; // E
  font[15][0] = 0xFE818181;
  font[15][1] = 0x81818181; // F
  font[16][0] = 0x00440000;
  font[16][1] = 0x18181818; // +
  font[17][0] = 0x18181818;
  font[17][1] = 0x00000000; // перевернутый символ 1

  // Открытие файла для записи
  file = fopen ("font.bin", "wb");
  if (file == NULL)
    {
      printf ("Ошибка открытия файла\n");
      return 1;
    }

  // Запись шрифта в файл
  fwrite (&fontsize, sizeof (int), 1, file);
  for (i = 0; i < FONT_SIZE; i++)
    {
      fwrite (font[i], sizeof (int), CHAR_SIZE, file);
    }

  fclose (file);
  printf ("Шрифт успешно сгенерирован и записан в файл font.bin\n");

  return 0;
}
