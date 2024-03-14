#!/bin/bash

# Очистка экрана
echo -e "\033[H\033[J"

# Переключение на дополнительную кодировочную таблицу
echo -e "\016" 

# Вывод рамки из символов псевдографики
row=10 # Начальная строка
col=5  # Начальный столбец
size=8 # Размер рамки (строки x столбцы)

# Верхняя граница
echo -e "\033[${row};${col}H╔$(printf -- '═%.0s' $(seq 1 $((size-2))))╗"

# Стороны и внутри
for ((i=1; i<size-1; i++)); do
    echo -e "\033[$((row+i));${col}H║"
    echo -e "\033[$((row+i));$((col+size-1))H║"
    for ((j=1; j<size-1; j++)); do
        echo -e "\033[$((row+i));$((col+j))H "
    done
done

# Нижняя граница
echo -e "\033[$((row+size-1));${col}H╚$(printf -- '═%.0s' $(seq 1 $((size-2))))╝"

# Вывод большого символа внутри рамки (последняя цифра дня рождения)
birthday_day=13 # Здесь нужно указать свой день рождения
symbol=$((birthday_day%10))
echo -e "\033[$((row+size/2));$((col+size/2-1))H${symbol}" # Символ псевдографики "закрашенный прямоугольник"

# Возврат к основной кодировочной таблице
echo -e "\017"

echo -e "\033[H\033[20;1H"
