#pragma once

enum State
{
  S0,
  S1
};

enum Symbol
{
  Z0,
  Z1
};

extern enum Symbol memory[100];
extern int position;
extern int shouldRun;

void step(void);