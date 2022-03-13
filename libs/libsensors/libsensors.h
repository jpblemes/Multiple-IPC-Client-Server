#ifndef LIBSENSORS_H_
#define LIBSENSORS_H_

#include "ipc_selector.h"

#define RESULT_SUCCESS  0
#define RESULT_FAIL    -1

int libsensors_start(int ipc_option);
int libsensors_clientSendValue(int num);
int libsensors_serverStart(void);

#endif // LIBSENSORS_H_