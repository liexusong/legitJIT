#include "timer.h"

struct timerVars tvars;

#ifdef __APPLE__
void initTiming(void)
{
  if( tvars.sTimebaseInfo.denom == 0 )
    (void)mach_timebase_info(&tvars.sTimebaseInfo);
}

void startTimer(void)
{
  tvars.start = mach_absolute_time();
}

void finishTimer(void)
{
  tvars.end = mach_absolute_time();
}

uint8_t getTimebaseNumer(void)
{
  return tvars.sTimebaseInfo.numer;
}

uint8_t getTimebaseDenom(void)
{
  return tvars.sTimebaseInfo.denom;
}

uint64_t getElapsedTime(void)
{
  tvars.elapsedNano = (tvars.end - tvars.start) * tvars.sTimebaseInfo.numer / tvars.sTimebaseInfo.denom;
  return tvars.elapsedNano;
}
#endif