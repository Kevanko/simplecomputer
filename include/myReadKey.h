#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

extern struct termios SETTINGS;

enum keys
{
  KEY_L,
  KEY_S,
  KEY_R,
  KEY_T,
  KEY_I,
  KEY_F5,
  KEY_F6,
  KEY_UP,
  KEY_DOWN,
  KEY_RIGHT,
  KEY_LEFT,
  KEY_ESC,
  KEY_ENTER,
  KEY_OTHER,
};

int rk_readkey (enum keys *);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout);