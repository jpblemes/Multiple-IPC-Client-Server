#ifndef LIBIPC_MSGQ_H_
#define LIBIPC_MSGQ_H_

#define RESULT_FAIL    -1
#define RESULT_SUCCESS  0

int server(void);
int client(int num);

#endif // LIBIPC_MSGQ_H_
