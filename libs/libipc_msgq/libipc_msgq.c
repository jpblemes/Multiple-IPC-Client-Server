#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "libipc_msgq.h"

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE     (MAX_MSG_SIZE + 10)
#define MSGQ_PERMISSIONS   0660
#define MSGQ_NAME_CLIENT "/msgqClient"
#define MSGQ_NAME_SERVER "/msgqServer"

#undef DEBUG
#undef DBG_PRINT
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

int server(void)
{
    fd_set readfds;
    char buffer[MSG_BUFFER_SIZE];
    int server_msgq_fd = 0;
    int client_msgq_fd = 0;
    /*setting message queue attributes*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    DBG_PRINT("Started IPC Message Queue Server!\n");

    if ( (server_msgq_fd = mq_open(MSGQ_NAME_SERVER, O_CREAT | O_RDONLY, MSGQ_PERMISSIONS, &attr)) == RESULT_FAIL) {
        DBG_PRINT("Server: mq_open failed\n");
        return RESULT_FAIL;
    }

    for(;;){
        FD_ZERO(&readfds);
        FD_SET(server_msgq_fd, &readfds);
        DBG_PRINT("Waiting for data from the client\n");
        select(server_msgq_fd + 1, &readfds, NULL, NULL, NULL);
        if(FD_ISSET(server_msgq_fd, &readfds)){
            memset(buffer, 0, MSG_BUFFER_SIZE);
            if (mq_receive(server_msgq_fd, buffer, MSG_BUFFER_SIZE, NULL) == RESULT_FAIL) {
                DBG_PRINT ("mq_receive error\n");
                return RESULT_FAIL;
            }
            DBG_PRINT("Data received by server: %s\n", buffer);
        }

        if ( (client_msgq_fd = mq_open(MSGQ_NAME_CLIENT, O_CREAT | O_WRONLY, MSGQ_PERMISSIONS, &attr)) == RESULT_FAIL ) {
            DBG_PRINT ("Server: mq_open failed\n");
            return RESULT_FAIL;
        }

        snprintf(buffer, MSG_BUFFER_SIZE, "IPC Message Queue Server returned success");
        DBG_PRINT("Send [%s] to client\n", buffer);
        if (mq_send(client_msgq_fd, buffer, strlen (buffer) + 1, 0) == RESULT_FAIL) {
            DBG_PRINT("Server: Not able to send message to client\n");
            return RESULT_FAIL;
        }
        mq_close(client_msgq_fd);
    }
    mq_close(server_msgq_fd);

    return RESULT_SUCCESS;
}

int client(int num)
{
    fd_set readfds;
    char buffer[MSG_BUFFER_SIZE];
    int server_msgq_fd = 0;
    int client_msgq_fd = 0;
    /*setting message queue attributes*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    snprintf(buffer, MSG_BUFFER_SIZE, "%d", num);

    if ( (server_msgq_fd = mq_open(MSGQ_NAME_SERVER, O_CREAT | O_WRONLY, 0, 0)) == RESULT_FAIL ) {
        DBG_PRINT ("Client: mq_open failed\n");
        return RESULT_FAIL;
    }

    if (mq_send (server_msgq_fd, buffer, strlen (buffer) + 1, 0) == RESULT_FAIL) {
        DBG_PRINT ("Client: Not able to send message to server\n");
        return RESULT_FAIL;
    }
    DBG_PRINT("Data sent to server: %s\n", buffer);

    if ( (client_msgq_fd = mq_open(MSGQ_NAME_CLIENT, O_CREAT | O_RDONLY, MSGQ_PERMISSIONS, &attr)) == RESULT_FAIL ) {
        DBG_PRINT ("Server: mq_open failed\n");
        return RESULT_FAIL;
    }

    FD_ZERO(&readfds);
    FD_SET(client_msgq_fd, &readfds);
    DBG_PRINT("Waiting for data from the server\n");
    select(client_msgq_fd + 1, &readfds, NULL, NULL, NULL);
    if(FD_ISSET(client_msgq_fd, &readfds)){
        memset(buffer, 0, MSG_BUFFER_SIZE);
        if (mq_receive(client_msgq_fd, buffer, MSG_BUFFER_SIZE, NULL) == RESULT_FAIL) {
            DBG_PRINT ("mq_receive error\n");
            return RESULT_FAIL;
        }
        DBG_PRINT("Result = %s\n", buffer);
    }
    mq_close(server_msgq_fd);
    mq_close(client_msgq_fd);

    return RESULT_SUCCESS;
}