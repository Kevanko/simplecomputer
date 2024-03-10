#include "mySimpleComputer.h"
#include "console.h"
#include "myTerm.h"

int TEST = 15;

void printMemory() {
    enum colors fg = GREEN, bg = BLACK;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (i == TEST) {
            fg = BLACK;
            bg = WHITE;
        } else {
            fg = GREEN;
            bg = BLACK;
        }
        printCell(i, fg, bg);
    }
}

void printTerm(int address, int input) {
    static int line = 0;
    mt_gotoXY(INOUT_BLOCK_X, INOUT_BLOCK_Y + line);
    if (input) {
        printf("%04X > +%04X", address, memory[address]);
    } else {
        printf("%04X < ", address);
    }
    line = (line + 1) % INOUT_BLOCK_HEIGHT;
}

// Приложение console
int main() {
    if (!isatty(STDOUT_FILENO)) {
        printf("Error: Output is not a terminal\n");
        return 1;
    }

    int rows, cols;
    mt_getscreensize(&rows, &cols);
    if (rows <  12 || cols < 20) {
        printf("Error: Terminal window is too small\n");
        return 1;
    }

    mt_clrscr();
    
    // Инициализация памяти, регистров и аккумулятора
    sc_memoryInit();
    sc_regInit();
    sc_accumulatorInit();
    sc_icounterInit();

    // Вывод текстовых данных консоли
    printMemory();
    printFlags();
    printDecodedCommand(15);
    printAccumulator();
    printCounters();

    // Вывод 7 произвольных ячеек в блок IN-OUT
    for (int i = 0; i < 7; i++) {
        printTerm(rand() % MEMORY_SIZE, 0);
    }

    mt_gotoXY(0, 25);
    return 0;
}