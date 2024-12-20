
#pragma once
#include <Arduino.h>
#define RPMS 30
#define STEPS_PER_REVOLUTION 2048
#define MAX_STEP_DELAY_MICROSECONDS 2000
#define MAX_ACCELERATION_STEPS 30


#define MAX_STEPS_PER_SECOND ((long)STEPS_PER_REVOLUTION * (long)RPMS / 60L) // Cast to long
#define DELAY_TARGET (1e6 / (long)MAX_STEPS_PER_SECOND) // Cast to long

const int speed_table[] PROGMEM = {0,1,5,11,19,30,44,60,78,99,122,147,175,206,239,274,312,352,394,439,487,537,589,644,701,761,823,887,954,1023};
