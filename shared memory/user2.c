#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

struct area
{
    int server;
    int client;
    int rw;
    char msg[50];
};

struct area *shmptr;

int main()
{
    int shmid;
    key_t key = 700;

    // Create or attach to the shared memory segment
    shmid = shmget(key, sizeof(struct area), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shmptr = (struct area *)shmat(shmid, NULL, 0);
    if (shmptr == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize flags
    shmptr->rw = 0;
    shmptr->server = 1;
    shmptr->client = 0;

    while (1)
    {
        // Wait for the client to become active
        while (shmptr->client == 0)
        {
            printf("Waiting for the client...\n");
            sleep(1);
        }

        // Prompt the user for a message
        printf("Enter a message: ");
        scanf("%49s", shmptr->msg);

        // Check if the message is "stop"
        if (strcmp(shmptr->msg, "stop") == 0)
        {
            shmptr->server = 0; // Set server flag to 0
            break; // Exit the loop
        }
        else
        {
            // Print the message received from the client
            printf("Received from the client: %s\n", shmptr->msg);
        }

        // Reset flags
        shmptr->server = 1;
        shmptr->client = 0;
    }

    // Detach from the shared memory segment
    if (shmdt(shmptr) == -1)
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
