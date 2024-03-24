#!/bin/bash

# Очистка экрана
echo -ne "\E[H\E[2J"

# Псевдографическая рамка
echo -ne "\E[10;5H"  # Перемещаем курсор на 10 строку, 5 символ
echo -ne "\E(0"       # Входим в режим альтернативного вывода символов
echo -ne "lqqqqqqqqk" # Верхняя граница рамки
echo -ne "\E[11;5H"   # Левая граница рамки
echo -e "x"
echo -ne "\E[11;14H"  # Правая граница рамки
echo -e "x"
echo -ne "\E[12;5H"
echo -e "x"
echo -ne "\E[12;14H"
echo -e "x"
echo -ne "\E[13;5H"
echo -e "x"
echo -ne "\E[13;14H"
echo -e "x"
echo -ne "\E[14;5H"
echo -e "x"
echo -ne "\E[14;14H"
echo -e "x"
echo -ne "\E[15;5H"
echo -e "x"
echo -ne "\E[15;14H"
echo -e "x"
echo -ne "\E[16;5H"
echo -e "x"
echo -ne "\E[16;14H"
echo -e "x"
echo -ne "\E[17;5H"
echo -e "x"
echo -ne "\E[17;14H"
echo -e "x"
echo -ne "\E[18;5H"
echo -e "x"
echo -e "\E[11;9Haaa" # Рисуем цифру 1
echo -e "\E[12;8Haa" 
echo -e "\E[12;10Haa"
echo -e "\E[13;10Haa"
echo -e "\E[14;10Haa"
echo -e "\E[15;10Haa"
echo -e "\E[16;10Haa"
echo -e "\E[17;10Haa"
echo -ne "\E[18;5H"
echo -e "mqqqqqqqqj" # Нижняя граница рамки
echo -ne "\E(B"       # Выходим из режима альтернативного вывода символов
