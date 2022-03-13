#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "libsensors.h"

#define LOWER 0
#define UPPER 10000

#undef DEBUG
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

int main(int argc, char** argv)
{
    int ipc_option, num;

    if( argc <= 1 ){
        DBG_PRINT("Please provide a value for the IPC\n")
        DBG_PRINT("Example:\n")
        DBG_PRINT("./testServer 0 &\n")
        DBG_PRINT("./testClient 0\n")
        return 0;
    }

    ipc_option = atoi(argv[1]);

    if( libsensors_start(ipc_option) == RESULT_FAIL ) {
        DBG_PRINT("libsensors_start failed!\n")
        return 0;
    }

    srand(time(NULL));
    num = (rand() % (UPPER - LOWER + 1)) + LOWER;
    DBG_PRINT("Random number generated: %d\n", num)

    if( libsensors_clientSendValue(num) == RESULT_FAIL) {
        DBG_PRINT("libsensors_clientSendValue failed!\n")
    }

    return 0;
}