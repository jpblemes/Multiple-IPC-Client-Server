# Multiple-IPC-App
- C aplication that has Linux IPC methods to be selected by the user.
The proposal of this program is just to use different Linux IPC methods.
- Included Linux IPC APIs:
  - Sockets
  - Message Queue
- Using dlopen/dlsyn to implement a good design for new ipc inclusion

### Getting started

- You can use docker to build and run the application in a Linux environment.

- Build the app
  - /your-dir-path/Multiple-IPC-App $ make
- To clean the build
  - /your-dir-path/Multiple-IPC-App $ make clean

### Execution

- Select the wanted IPC:
  - 0 - Sockets
  - 1 - Message Queue
- Execute the server in background with the ipc flag you want:
  - /your-dir-path/Multiple-IPC-App $ ./build/testServer 0 &
  - /your-dir-path/Multiple-IPC-App $ ./build/testServer 1 &
- "testClient" generates a random number that is sent to the server using the client. Just execute with the ipc flag you want:
  - /your-dir-path/Multiple-IPC-App $ ./build/testClient 0
  - /your-dir-path/Multiple-IPC-App $ ./build/testClient 1

### Details

- The server will show the number received
- The client receive from the server a result message

### Improvements

- This system is designed just for 1 server x 1 client communication.
- For multiple clients/servers the ipc libraries have to be modified and a semaphore is needed
