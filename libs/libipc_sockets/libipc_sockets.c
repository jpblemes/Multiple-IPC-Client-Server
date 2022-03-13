#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "libipc_sockets.h"

#undef DEBUG
#define DEBUG

#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("%s %s Line:%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__);
#else
    #define DBG_PRINT(fmt, ...)
#endif // DEBUG

#define SOCKET_NAME "/tmp/sensorSocket"
#define BUFFER_SIZE 128
#define RESULT_SUCCESS  0
#define RESULT_FAIL    -1

int server(void)
{
    struct sockaddr_un name;

    int ret;
    int connection_socket;
    int data_socket;
    char buffer[BUFFER_SIZE];

    DBG_PRINT("Started IPC Socket Server!\n")

    /*In case the program exited inadvertently on the last run, remove the socket. **/
    unlink(SOCKET_NAME);

    /* Create Master socket. */
    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (connection_socket == -1) {
        perror("socket");
        return RESULT_FAIL;
    }
    
    DBG_PRINT("Master socket created\n")

    /*initialize*/
    memset(&name, 0, sizeof(struct sockaddr_un));

    /*Specify the socket Cridentials*/
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

    /* Bind socket to socket name.*/
    ret = bind(connection_socket, (const struct sockaddr *) &name,
            sizeof(struct sockaddr_un));

    if (ret == -1) {
        perror("bind");
        return RESULT_FAIL;
    }
    DBG_PRINT("bind() call succeed\n")
    
    /* Prepare for accepting connections. The backlog size is setted. */
    ret = listen(connection_socket, 20);
    if (ret == -1) {
        perror("listen");
        return RESULT_FAIL;
    }

    /*loop for handling connections. */
    for (;;) {

        /* Wait for incoming connection. */
        DBG_PRINT("Waiting on accept() sys call\n")

        data_socket = accept(connection_socket, NULL, NULL);

        if (data_socket == -1) {
            perror("accept");
            return RESULT_FAIL;
        }
        
        DBG_PRINT("Connection accepted from client\n")

        /*Prepare the buffer to recv the data*/
        memset(buffer, 0, BUFFER_SIZE);

        /* Wait for next data packet. 'read' is a blocking system call*/
        DBG_PRINT("Waiting for data from the client\n")
        ret = read(data_socket, buffer, BUFFER_SIZE);

        if (ret == -1) {
            perror("read");
            return RESULT_FAIL;
        }

        /* show received value. */
        DBG_PRINT("data received by server: %s\n", buffer)

        /* Send ok. */
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "IPC Socket Server returned success");

        DBG_PRINT("Send [%s] to client\n", buffer);
        ret = write(data_socket, buffer, BUFFER_SIZE);
        if (ret == -1) {
            perror("write");
            return RESULT_FAIL;
        }

        /* Close socket. */
        close(data_socket);
    }

    /*close the master socket*/
    close(connection_socket);
    DBG_PRINT("connection closed..\n");

    /* Unlink the socket. */
    unlink(SOCKET_NAME);
    return RESULT_SUCCESS;
}

int client (int value)
{
    struct sockaddr_un addr;
    int ret;
    int data_socket;
    char buffer[BUFFER_SIZE];

    /* Create data socket. */
    data_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (data_socket == -1) {
        perror("socket");
        return RESULT_FAIL;
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));

    /* Connect socket to socket address */
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

    ret = connect (data_socket, (const struct sockaddr *) &addr,
            sizeof(struct sockaddr_un));

    if (ret == -1) {
        fprintf(stderr, "The server is down.\n");
        return RESULT_FAIL;
    }

    /* Send arguments. */
    memset(buffer, 0, BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE, "%d", value);

    ret = write(data_socket, buffer, BUFFER_SIZE);
    if (ret == -1) {
        perror("write");
    }
    DBG_PRINT("Data sent to server: %d\n", value)

    /* Receive result. */
    memset(buffer, 0, BUFFER_SIZE);
    
    ret = read(data_socket, buffer, BUFFER_SIZE);
    if (ret == -1) {
        perror("read");
        return RESULT_FAIL;
    }

    /* Ensure buffer is 0-terminated. */

    buffer[BUFFER_SIZE - 1] = 0;

    DBG_PRINT("Result = %s\n", buffer)

    /* Close socket. */

    close(data_socket);

    return RESULT_SUCCESS;
}
