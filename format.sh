#!/bin/bash

# Найти все файлы с расширением .c и .h в текущем каталоге и его подкаталогах
files=$(find . -type f \( -name "*.c" -o -name "*.h" \))

# Переменная для хранения отформатированных файлов
formatted_files=""

# Применить clang-format к каждому найденному файлу
for file in $files; do
    # Сохраняем хэш-сумму файла до форматирования
    original_hash=$(md5sum "$file" | awk '{print $1}')
    # Применяем clang-format к файлу
    clang-format -style=gnu "$file" -i
    # Получаем хэш-сумму файла после форматирования
    formatted_hash=$(md5sum "$file" | awk '{print $1}')
    # Проверяем, изменился ли файл после форматирования
    if [ "$original_hash" != "$formatted_hash" ]; then
        formatted_files+="$file\n"
    fi
done

# Проверяем, были ли отформатированы какие-либо файлы
if [ -n "$formatted_files" ]; then
    echo "Отформатированные файлы:"
    echo -e "$formatted_files"
else
    echo "Нет файлов, которые нужно было отформатировать."
fi
