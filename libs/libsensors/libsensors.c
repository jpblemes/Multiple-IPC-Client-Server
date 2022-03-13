#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

#include "libsensors.h"

#undef DEBUG
#undef DBG_PRINT
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

static int libsensors_init = 0;

/** @brief Sets the selected ipc method */
int libsensors_start(int ipc_option)
{
    if(selectIPC(ipc_option) == RESULT_FAIL) {
        DBG_PRINT("Failed to load IPC lib.\n");
        return RESULT_FAIL;
    }
    libsensors_init = 1;

    return RESULT_SUCCESS;
}

/** @brief Interface that starts the server */
int libsensors_serverStart(void)
{
    if(!libsensors_init){
        DBG_PRINT("libsensors not started!\n");
        return RESULT_FAIL;
    }

    if( RESULT_SUCCESS != server() ){
        DBG_PRINT("server failed\n");
    }

    return RESULT_SUCCESS;
}

/** @brief Interface to receive value that will be sent using the client */
int libsensors_clientSendValue(int num)
{
    if(!libsensors_init){
        DBG_PRINT("libsensors not started!\n");
        return RESULT_FAIL;
    }

    if( RESULT_SUCCESS != client(num) ){
        DBG_PRINT("client failed\n");
    }

    return RESULT_SUCCESS;
}