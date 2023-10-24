// TODO: add the appropriate head files here
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "lab2.h"

/************************************************************\
 * get_arguments - returns the command line arguments not
 *                 including this file in an array with the
 *                 last element as null.  This is the format
 *                 that the execvp() function requires.
 * 
 * For example:  ./time ls -l
 * will return an array consisting of {"ls","-l", NULL}
 ************************************************************/
char** get_arguments(int argc, char** argv) {
    int arg_length = argc - 1;
    char** cmd_args = (char**)malloc(sizeof(char*) * arg_length);
    for (int i = 0; i < arg_length; i++) {
        cmd_args[i] = argv[i + 1];
    }
    cmd_args[arg_length] = NULL;
    return cmd_args;
}

int main(int argc, char** argv) {
    pid_t pid;
    int status = 1; // Define status as 1 to assume that the child process is not finished (0 if it is done)
    char* ipc_ptr = NULL; // pointer to shared memory
    struct timeval start_time;
    struct timeval current_time;

    if (argc < 2) {
        fprintf(stderr, "SYNOPSIS: %s <cmd> <cmd arguments>\n", argv[0]);
        return 1;
    }

    // call ipc_create to create shared memory region to which parent and child have access.
    ipc_ptr = ipc_create(sizeof(time_t)); // Ensure you're creating shared memory for a time_t value

    pid = fork(); // fork a child process

    if (pid < 0) { // if an error occurred
        fprintf(stderr, "Fork failed!\n");
        return 2;
    } else if (pid == 0) { // if it is a child process
        gettimeofday(&start_time, NULL); // Grab the start time
        time_t start_time_useconds = start_time.tv_usec; // Grab the start time in seconds

        printf("\n Child Function \n");
        printf("start_time.tv_usec: %ld\n", (long)start_time.tv_usec);

        // Write start_time_seconds (in microseconds) to shared memory
        memcpy(ipc_ptr, &start_time, sizeof(time_t));

        char** command_args = get_arguments(argc, argv); // get the list of arguments to be used in execvp() and execute execvp()
        execvp(command_args[0], command_args); // runs execvp using already initialized variables
        // For reference, command_args[0] holds the name, which would be "time" or "./time"
        // then you pass command_args because that holds all of the relevant information in an array

        fprintf(stderr, "Child Process is Complete\n");
        status = 0; // Sets the status flag for the child process to 0 to indicate the child process is completed
    } else { // if it is a parent process
        wait(NULL); // Waits for the child process, uses NULL as arg because there is only 1 child process

        gettimeofday(&current_time, NULL); // Grab the current time
        time_t current_time_seconds = current_time.tv_usec; // Grab the current time in seconds

        // Read start_time_seconds from shared memory
        time_t start_time_useconds;
        memcpy(&start_time_useconds, ipc_ptr, sizeof(time_t));

        if (start_time_useconds == 0) {
            fprintf(stderr, "\n IPC SHARED MEMORY DID NOT WORK. \n");
            exit(1);
        }
        
        printf("\n Parent Function \n");
        printf("start time from IPC: %ld \n", start_time_useconds);
        printf("current_time.tv_usec: %ld\n", (long)current_time.tv_usec);

        ipc_close(); // Closes shared memory communication
        printf("Parent Process is Complete\n");

        // NOTE: DO NOT ALTER THE LINE BELOW.
        printf("Elapsed time %.5f\n",elapsed_time(&start_time, &current_time));
    }

    return status;
}
