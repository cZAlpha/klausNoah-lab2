#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    double elapsed_time; // a double-type variable that holds the amount of time IN SECONDS that has elapsed
    
    // BOTH end_time AND start_time MUST BE IN SECONDS. 
    // EITHER DO CONVERSION IN APPLICABLE FUNCTION AND FILE,
    // OR DO IT RIGHT BEFORE THE NEXT LINE THAT USES "difftime" (see below)
    elapsed_time = difftime(end_time, start_time);

    return elapsed_time;
}
