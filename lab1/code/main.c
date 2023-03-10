// Main file of the serial port project.
// NOTE: This file must not be changed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "application_layer.h"

#define BAUDRATE 9600
#define N_TRIES 3
#define TIMEOUT 3

clock_t start;
clock_t end;

// Arguments:
//   $1: /dev/ttySxx
//   $2: tx | rx
//   $3: filename
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s /dev/ttySxx tx|rx filename\n", argv[0]);
        exit(1);
    }

    const char *serialPort = argv[1];
    const char *role = argv[2];
    const char *filename = argv[3];

    printf("Starting link-layer protocol application\n"
           "  - Serial port: %s\n"
           "  - Role: %s\n"
           "  - Baudrate: %d\n"
           "  - Number of tries: %d\n"
           "  - Timeout: %d\n"
           "  - Filename: %s\n",
           serialPort,
           role,
           BAUDRATE,
           N_TRIES,
           TIMEOUT,
           filename);

    if (applicationLayer(serialPort, role, BAUDRATE, N_TRIES, TIMEOUT, filename) < 0 )
        appLayer_exit();

    // data transfer 
    int res;
    start = clock();
    if ((strcmp(role, "rx")) == 0) {
        printf("Receiving file...\n\n");
        res = readFile();
        if  (res == 0) {
            printf("File read is empty. \n\n");
        }
        else if (res == -1) {
            printf("File read error. \n\n");
        }
    }
    else if ((strcmp(role, "tx")) == 0) {
        printf("Sending file...\n\n");
        res = sendFile(filename);
        if (res == -1) {
            printf("File send error. \n\n");
        }
    }
    else {
        printf("No discernible role in arguments. \n");
    }

    appLayer_exit();
    clock_t end = clock();
    printf("Time taken: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    return res;
}
