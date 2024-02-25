#!/bin/bash

# Найти все файлы с расширением .c в текущем каталоге и его подкаталогах
files=$(find . -name "*.c")

# Применить clang-format к каждому найденному файлу
for file in $files; do
clang-format -style=gnu $file -i
done

echo "Форматирование завершено."