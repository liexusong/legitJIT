/*
===============================================================================================
Name         :  timerh
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014 Description : This is the timer interface
===============================================================================================
*/

#ifndef TIMER_H_
#define TIMER_H_

#ifdef __APPLE__
  #include <sys/time.h>
  #include <mach/mach_time.h>
#endif

#include <unistd.h>
#include <time.h>

struct timerVars
{
  uint64_t        start;
  uint64_t        end;
  uint64_t        elapsedNano;

#ifdef __APPLE__
  mach_timebase_info_data_t sTimebaseInfo;
#endif
};

void initTiming(void);

extern inline void startTimer(void);
extern inline void finishTimer(void);

#ifdef __APPLE__
extern inline uint8_t getTimebaseNumer(void);
extern inline uint8_t getTimebaseDenom(void);
#endif

extern uint64_t getElapsedTime(void);

#endif /* TIMER_H_ */
