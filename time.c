#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    double elapsed_time_in_seconds; // a double-type variable that holds the amount of time IN SECONDS that has elapsed
    double startTimeSeconds = start_time->tv_sec + (start_time->tv_usec / 1000000.0); // math
    double endTimeSeconds =   end_time->tv_sec     + (end_time->tv_usec / 1000000.0);   // math
    elapsed_time_in_seconds = endTimeSeconds - startTimeSeconds; // Does the math, both args are already in seconds due to main.c

    // UNCOMMENT FOR TESTING BELOW
    // printf("\n FROM IPC \n");
    // printf("Start Time Seconds: %d \n", startTimeSeconds);
    // printf("End Time Seconds:   %d \n", endTimeSeconds);
    // printf("Elapsed Time In Seconds: %d \n\n", elapsed_time_in_seconds);
    // UNCOMMENT FOR TESTING ABOVE

    return elapsed_time_in_seconds;
}
