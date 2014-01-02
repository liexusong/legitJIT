/*
 ===============================================================================================================================
 Name        : asmInstructions.h
 Author      : Vs37nX
 Version     : 0.2
 Copyright   : You can copy any part of this code AS LONG as you mention me somewhere in the projects credits or contributors
 Description : This is the implementation for all the timer functions
 ===============================================================================================================================
 */

#include <stdio.h>    			/** Printf 				**/

#include "timer.h"

/** call this function to start a nanosecond-resolution timer **/
struct timespec timer_start(void){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}


float timer_end(struct timespec start_time){
	long int diffInNanos;
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	diffInNanos = end_time.tv_nsec - start_time.tv_nsec;
	return (float)diffInNanos;
}

void reportTime(char* str, float elapsedTime)
{
	printf("%s = %f, Time taken (nanoseconds)\n", str, elapsedTime);
	time_elapsed_nanos = 0.0;
}

void startTimer(void)
{
	vartime = timer_start();  /** begin a timer called 'vartime' **/
}

void stopTimer(void)
{
	time_elapsed_nanos = timer_end(vartime);
}
