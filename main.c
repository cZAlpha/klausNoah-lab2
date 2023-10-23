// TODO: add the appropriate head files here
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
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
char** get_arguments(int argc, char** argv){
    int arg_length = argc;
    char**  cmd_args = NULL;

    if (arg_length > 0){
        cmd_args = (char**)malloc(sizeof(char*)*arg_length);
    }
    for(int i = 0; i < arg_length-1; i++){
        cmd_args[i] = argv[i+1];
    }
    cmd_args[arg_length-1] = NULL;
    return cmd_args;
}


int main(int argc, char** argv)
{
    pid_t pid;
    int status = 1; // Define status as 1 to assume that child process is not finished (0 if it is done)
    char* command = NULL;
    char** command_args = NULL;
    char* ipc_ptr = NULL; // pointer to shared memory
    struct timeval start_time;
    struct timeval current_time;

    if (argc < 2){
        fprintf(stderr,"SYNOPSIS: %s <cmd> <cmd arguments>\n",argv[0]);
        return 1;
    }
    
    // TODO: call ipc_create to create shared memory region to which parent
    //       child have access.
    ipc_ptr = ipc_create(sizeof(start_time));
    pid = fork(); /* fork a child process */

    if (pid < 0) { /* if an error occurred */
        fprintf(stderr, "Fork failed!");
        return 2;
    }
    else if (pid == 0) { /* if it is a child process */
        // TODO: use gettimeofday to log the start time
        gettimeofday(&start_time, NULL); // Grabbing start time
        time_t start_time_seconds = start_time.tv_sec; // Grabbing specifically start time in seconds

        // TODO: write the time to the IPC
                // Likely will have to specifically only change pointers and stuff instead
                // of actually referring to the values, due to C being C
        
        // TODO: get the list of arguments to be used in execvp() and execute execvp()

        printf("Child Process is Complete \n");
        status = 0; // Sets the status flag for the child process to 0 to indicate the child process is completed
    }
    else { /* if it is a parent process */
        wait(NULL); // Waits for child process, uses NULL as arg because there is only 1 child process 

        // TODO: getcurrent_time the current time using gettimeofday
        gettimeofday(&current_time, NULL); // Grabbing current time
        time_t current_time_seconds = current_time.tv_sec; // Grabbing specifically current time in seconds
        
        // TODO: read the start time from IPC
            // This will grab the start time from the child object through the IPC shared memory
        
        // TODO: close IPC
        ipc_close();
        printf("Parent Process is Complete \n"); 

        // NOTE: DO NOT ALTER THE LINE BELOW.
        printf("Elapsed time %.5f\n",elapsed_time(&start_time, &current_time));
    }
    
    return status;
}