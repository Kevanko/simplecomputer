#!/bin/bash

# Очистка экрана и перемещение курсора в левый верхний угол
clear_screen="\033[H\033[2J"
# Перемещение курсора в заданную позицию на экране
cursor_address="\033[%d;%dH"
# Задание цвета фона для последующих символов
set_a_background="\033[%dm"
# Задание цвета текста для последующих символов
set_a_foreground="\033[%dm"
# Скрытие курсора
cursor_invisible="\033[?25l"
# Показ курсора
cursor_visible="\033[?25h"
# Очистка текущей строки
delete_line="\033[K"

# Escape-последовательности
red_on_black="\033[31;40m"
green_on_white="\033[32;47m"
default_color="\033[0m"
cursor_position="\033[5;10H"
cursor_position_group="\033[6;8H"
cursor_reset="\033[H\033[10;1H"

# Очистка экрана
echo -e "${clear_screen}"

# Вывод имени красным цветом на черном фоне
echo -e "${cursor_position}${red_on_black}Михаил Николаенков"

# Вывод группы зеленым цветом на белом фоне
echo -e "${cursor_position_group}${green_on_white}Ив-222"

# Возвращение настроек цвета по умолчанию и перемещение курсора
echo -e "${default_color}${cursor_reset}"
