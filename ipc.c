// TODO: add the appropriate header files here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>


/**************************************************************
 *  ipc_create - creates a shared memory object called lab2 and
 *               returns a char pointer to the memory shared
 *               memory object.
 * 
 *  size - is the size of the memory object to create.
 ***************************************************************/
char* ipc_create(int size) {
    int shmid;  /* Shared memory ID */
    char* ptr;  /* Pointer to shared memory object */
    const char *name = "/lab2";

    // Create the shared memory object called "lab2"
    shmid = shmget(ftok(name, 1), size, IPC_CREAT | 0666);

    // Configure the size of the shared memory object
    // (This step is already included in the shmget function)

    // Memory map the shared memory object
    // TODO: Memory map the shared memory object here
    ptr = shmat(shmid, NULL, 0);
    if (ptr == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    return ptr;
}



/**************************************************************
 * ipc_close - closes the ipc communication channel that was
 *             created with ipc_create.
 **************************************************************/
void ipc_close() {
    shm_unlink("lab2");
}