#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //dlopen and dlsym

#include "ipc_selector.h"

#undef DEBUG
//#define DEBUG /*uncomment to debug*/

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

static void *handle = NULL;

enum ipc_id{
    sockets,
    messageQueue
};

static ipc ipc_list[] = {
    {sockets, "Sockets", "shared/libipc_sockets.so"},
    {messageQueue, "Message Queue", "shared/libipc_msgq.so"}
};

/** @brief Set the shared library according to the received ipc_option (id) */
int selectIPC(int ipc_option)
{
    unsigned int i;

    ipc ipc_selected = {RESULT_FAIL, "", ""};

    for (i=0; i<sizeof(ipc_list); i++) {
        if (ipc_list[i].id == ipc_option) {
            ipc_selected = ipc_list[i];
            break;
        }
    }

    if(ipc_selected.id == RESULT_FAIL) {
        DBG_PRINT("Invalid ipc method\n");
        return RESULT_FAIL;
    }

    DBG_PRINT("IPC selected: id=[%d] name=[%s] path=[%s]\n", ipc_selected.id, ipc_selected.name, ipc_selected.path);
    if(handle != NULL)
    {
        DBG_PRINT("Handle already loaded\n");
        return RESULT_SUCCESS;
    }

    DBG_PRINT("Loading handler\n");
    handle = dlopen(ipc_selected.path, RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        DBG_PRINT("%s\n", dlerror());
        return RESULT_FAIL;
    }

    return RESULT_SUCCESS;
}

/** @brief Wrapper for server function. Set the correct symbol according to the selected
 * shared library */
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

/** @brief Wrapper for client function. Set the correct symbol according to the selected
 * shared library
*/
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