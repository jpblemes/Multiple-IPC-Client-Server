# Multiple-IPC-App
C aplication that has Linux IPC methods to be selected by the user.
The proposal of this program is just to use different Linux IPC methods.

### Getting started

- You can use docker to build and run the application in a Linux environment. Just use the dockerfile.

- Build the app
  - /your-dir-path/Multiple-IPC-App $ make
- To clean the build
  - /your-dir-path/Multiple-IPC-App $ make clean

### Execution

- Execute the server in background
  - /your-dir-path/Multiple-IPC-App $ ./build/testServer &
- Generate a random number and send it to the server using the client
  - /your-dir-path/Multiple-IPC-App $ ./build/testClient 

### Details

- The server will show the number received
- The client receive from the server a result message
