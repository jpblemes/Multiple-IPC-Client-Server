#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <time.h>

#include "libsensors.h"
#include "ipc_sockets.h"

#undef DEBUG
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

#define RESULT_SUCCESS  0
#define RESULT_FAIL    -1

//Function that starts server
int dataServer_start(void)
{
    if( RESULT_SUCCESS != server() ){
        DBG_PRINT("server failed\n");
    }

    return RESULT_SUCCESS;
}

//Function for client command
int dataClient_sendCommand(void)
{   
    srand(time(NULL));
    int lower = 1, upper = 10000;
    int num = (rand() % (upper - lower + 1)) + lower;
    DBG_PRINT("Random number generated: %d\n", num);
    
    if( RESULT_SUCCESS != client(num) ){
        DBG_PRINT("client failed\n");
    }

    return RESULT_SUCCESS;
}