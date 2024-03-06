#pragma once
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>

void printCell (int address, enum colors fg, enum colors bg);
void printFlags ();
void printDecodedCommand (int value);
void printAccumulator ();
void printCounters ();