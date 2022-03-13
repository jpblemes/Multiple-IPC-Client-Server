#ifndef IPC_SELECTOR_H_
#define IPC_SELECTOR_H_

#define RESULT_SUCCESS  0
#define RESULT_FAIL    -1

typedef struct ipc{
    int id;
    char* name;
    char* path;
}ipc;

int selectIPC(int ipc_option);
int server(void);
int client(int value);

#endif // IPC_SELECTOR_H_