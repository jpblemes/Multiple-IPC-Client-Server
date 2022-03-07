#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //dlopen and dlsym

#include "libsensors.h"

#undef DEBUG
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

//Dynamic open the chosen lib
#define LIBIPC_SOCKETS_PATH "shared/libipc_sockets.so"

static void *handle = NULL;

int selectIPC(void)
{
    if(handle != NULL)
    {
        DBG_PRINT("Handle already loaded\n");
        return RESULT_SUCCESS;
    }

    DBG_PRINT("Loading IPC SOCKETS handler\n");
    handle = dlopen(LIBIPC_SOCKETS_PATH, RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        DBG_PRINT("%s\n", dlerror());
        return RESULT_FAIL;
    }

    return RESULT_SUCCESS;
}

int server(void)
{
    if(handle == NULL){
        DBG_PRINT("handle == NULL!\n");
        return RESULT_FAIL;
    }

    int (*select_server)(void);
    select_server = dlsym(handle, "server");
    if (select_server == NULL) {
        DBG_PRINT("Error: %s\n", dlerror()); /* no such symbol */
        return RESULT_FAIL;
    }

    return select_server();
}

int client(int value)
{
    if(handle == NULL){
        DBG_PRINT("handle == NULL!\n");
        return RESULT_FAIL;
    }

    int (*select_client)(int);
    select_client = dlsym(handle, "client");
    if (select_client == NULL) {
        DBG_PRINT("Error: %s\n", dlerror()); /* no such symbol */
        return RESULT_FAIL;
    }

    return select_client(value);
}