#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libsensors.h"

#undef DEBUG
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

int main(int argc, char** argv)
{
    int ipc_option;

    if(argc <= 1){
        DBG_PRINT("Please provide a value for the IPC\n");
        DBG_PRINT("Example:\n");
        DBG_PRINT("./testServer 0 &\n");
        DBG_PRINT("./testClient 0\n");
        return 0;
    }

    ipc_option = atoi(argv[1]);

    if( libsensors_start(ipc_option) == RESULT_FAIL ) {
        DBG_PRINT("libsensors_start failed!\n");
        return 0;
    }

    if( libsensors_serverStart() == RESULT_FAIL) {
        DBG_PRINT("libsensors_serverStart failed!\n");
    }

    return 0;
}