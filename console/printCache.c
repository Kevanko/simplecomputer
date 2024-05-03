#include"console.h"

void printCache(){

    for(int i = 0; i < 5; i++){
        mt_gotoXY (2, 20 + i);
        printf ("%d0:", cache[i].c_number);
        for(int j = 0; j < 10; j++){
            mt_gotoXY (6 + j * 6, 20 + i);
            printf ("+%04X", cache[i].c_line[j]);
        }
    }
 
}