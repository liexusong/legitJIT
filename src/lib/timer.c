#include "timer.h"

struct timerVars tvars;

#ifdef __APPLE__
void initTiming(void)
{
  if(tvars.sTimebaseInfo.denom == 0 )
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
#elif __linux__

void initTiming(void)
{
  tvars.TS.tv_sec  = 0; // s
  tvars.TS.tv_nsec = 1; // ns
}

void startTimer(void)
{
  clock_gettime(CLOCK_REALTIME, &tvars.start);
}

void finishTimer(void)
{
  clock_gettime(CLOCK_REALTIME, &tvars.end);
}

uint8_t getTimebaseNumer(void)
{
  return 1;
}

uint8_t getTimebaseDenom(void)
{
  return 1;
}

uint64_t getElapsedTime(void)
{
  tvars.elapsedNano = ((double)tvars.end.tv_sec*SEC2NANOSEC   + (double)tvars.end.tv_nsec  )
                    - ((double)tvars.start.tv_sec*SEC2NANOSEC + (double)tvars.start.tv_nsec);

  return tvars.elapsedNano;
}

#endif
