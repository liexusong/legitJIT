#ifndef TIMER_H_
#define TIMER_H_

#define SEC2NANOSEC 1000000000

#ifdef __APPLE__
  #include <sys/time.h>
  #include <mach/mach_time.h>
#endif

#include <unistd.h>
#include <stdint.h>
#include <time.h>

struct timerVars
{
#ifdef __APPLE__
  uint64_t        start, end, elapsedNano;
  mach_timebase_info_data_t sTimebaseInfo;
#elif  __linux__
  struct timespec start, end, TS;
  uint64_t elapsedNano;
#elif _WIN32

#endif
};

extern inline void initTiming(void);

extern inline void startTimer(void);
extern inline void finishTimer(void);

extern uint64_t getElapsedTime(void);

#endif /* TIMER_H_ */
