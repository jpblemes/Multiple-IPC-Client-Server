PWD = $(shell pwd)
SHARED_DIR = $(PWD)/../../shared

CC = gcc  # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g  # C flags
LDFLAGS = -shared -pthread# linking flags

RM = rm -f   # rm command
TARGET_LIB = libipc_sockets.so  # target lib
SRCS = libipc_sockets.c # source files
OBJS = $(SRCS:.c=.o)

all: ${TARGET_LIB}
	$(shell mv ${TARGET_LIB} $(SHARED_DIR))

$(TARGET_LIB): $(OBJS)
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)