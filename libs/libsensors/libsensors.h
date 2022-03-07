#ifndef LIBSENSORS_H_
#define LIBSENSORS_H_

#define RESULT_SUCCESS  0
#define RESULT_FAIL    -1

int dataClient_sendCommand(void);
int dataServer_start(void);

//IPC SELECTOR
int selectIPC(void);
int server(void);
int client(int value);

#endif // LIBSENSORS_H_