/*
 ===============================================================================================================================
 Name        : timer.h
 Author      : Vs37nX
 Version     : 0.2
 Copyright   : You can copy any part of this code AS LONG as you mention me somewhere in the projects credits or contributors
 Description : This is the header interface for all the timer functions
 ===============================================================================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>
#include <sys/time.h>

struct timespec vartime;
float time_elapsed_nanos;
struct timespec start_time;

struct timespec timer_start();
float timer_end(struct timespec start_time);
void reportTime(char* str, float elapsedTime);

void startTimer();
void stopTimer();
void initTimer();

#endif /* TIMER_H_ */
