PWD = $(shell pwd)
SHARED_DIR = $(PWD)/../../shared#.so folder path

CC = gcc  # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g# C flags
LDFLAGS += -shared -W# linking flags
DYNAMIC_LINKER = -ldl

RM = rm -f   # rm command
TARGET_LIB = libsensors.so  # target lib
SRCS = libsensors.c ipc_selector.c # source files
OBJS = $(SRCS:.c=.o)

all: ${TARGET_LIB}
	$(shell mv ${TARGET_LIB} $(SHARED_DIR))

$(TARGET_LIB): $(OBJS)
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^ $(DYNAMIC_LINKER)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< > $@

include $(SRCS:.c=.d)

clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)