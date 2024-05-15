#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct STACK
{
  char c;
  struct STACK *next;
};

struct STACK *stack_push (struct STACK *head, char a);
char stack_pop (struct STACK **head);
int get_prior (char c);
void translate_to_rpn (char *outstr, char *a);