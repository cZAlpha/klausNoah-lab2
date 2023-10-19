#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    double elapsed_time; // a double-type variable that holds the amount of time IN SECONDS that has elapsed
    
    elapsed_time = difftime(end_time, start_time); // Does the math, both args are already in seconds due to main.c

    return elapsed_time;
}
