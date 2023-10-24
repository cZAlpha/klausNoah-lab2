#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    double elapsed_time; // a double-type variable that holds the amount of time IN SECONDS that has elapsed
    double startTimeSeconds = (start_time->tv_usec * 1000000);
    double endTimeSeconds   = (end_time->tv_usec * 1000000);

    elapsed_time = (startTimeSeconds - endTimeSeconds) / 1000000; // Does the math, both args are already in seconds due to main.c

    return elapsed_time;
}
