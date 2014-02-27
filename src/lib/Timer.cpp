// File: Timer.cpp
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>


#include <cstdlib>
#include "Timer.h"

Timer::Timer() {
#ifdef WIN32
    QueryPerformanceFrequency(&freq);
    startCount.QuadPart = 0;
    endCount.QuadPart = 0;
#else
    startCount.tv_sec = startCount.tv_usec = 0;
    endCount.tv_sec = endCount.tv_usec = 0;
#endif
	reset();
}

void Timer::reset() {
    stopped = 0;
#ifdef WIN32
    QueryPerformanceCounter(&startCount);
#else
    gettimeofday(&startCount, NULL);
#endif
}

void Timer::stop() {
    stopped = 1;

#ifdef WIN32
    QueryPerformanceCounter(&endCount);
#else
    gettimeofday(&endCount, NULL);
#endif
}

double Timer::get_time_microsec() {
#ifdef WIN32
    if(!stopped) QueryPerformanceCounter(&endCount);
    double start = startCount.QuadPart * ((double)1e6 / freq.QuadPart);
    double end = endCount.QuadPart * ((double)1e6 / freq.QuadPart);
#else
    if(!stopped) gettimeofday(&endCount, NULL);
    double start = ((int)startCount.tv_sec * 1e6) + (int)startCount.tv_usec;
    double end = ((int)endCount.tv_sec * 1e6) + (int)endCount.tv_usec;
#endif

    return end - start;
}
