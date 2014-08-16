#include "timer.h"

struct timerVars tvars;

void initTiming(void)
{
#ifdef __APPLE__
  if(tvars.sTimebaseInfo.denom == 0 )
    (void)mach_timebase_info(&tvars.sTimebaseInfo);
#elif __linux__
  tvars.TS.tv_sec  = 0; // s
  tvars.TS.tv_nsec = 1; // ns
#elif _WIN32

#endif
}

void startTimer(void)
{
#ifdef __APPLE__
  tvars.start = mach_absolute_time();
#elif __linux__
  clock_gettime(CLOCK_REALTIME, &tvars.start);
#elif _WIN32

#endif
}

void finishTimer(void)
{
#ifdef __APPLE__
  tvars.end = mach_absolute_time();
#elif __linux__
  clock_gettime(CLOCK_REALTIME, &tvars.end);
#elif _WIN32

#endif
}

uint64_t getElapsedTime(void)
{
#ifdef __APPLE__
  tvars.elapsedNano = (tvars.end - tvars.start) * tvars.sTimebaseInfo.numer / tvars.sTimebaseInfo.denom;
  return tvars.elapsedNano;
#elif __linux__
  tvars.elapsedNano = ((double)tvars.end.tv_sec*SEC2NANOSEC   + (double)tvars.end.tv_nsec  )
                    - ((double)tvars.start.tv_sec*SEC2NANOSEC + (double)tvars.start.tv_nsec);

  return tvars.elapsedNano;
#elif _WIN32

#endif
}
