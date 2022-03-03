PWD = $(shell pwd)
BUILD_DIR = $(PWD)/../build
SHARED_DIR = $(PWD)/../shared
INCLUDE_DIR = -I$(PWD)/../libsensors
LIBS_DIR = -L$(PWD)/../libsensors
LIBS = -lsensors

CC = gcc  # C compiler
CFLAGS = -Wall -Wextra -g $(INCLUDE_DIR) # C flags
LDFLAGS = -L$(SHARED_DIR) -Wl,-rpath,$(SHARED_DIR)
LDFLAGS += $(LIBS_DIR) $(LIBS)
RM = rm -f   # rm command
TARGET_EXEC = testClient  # target exec
SRCS = testClient.c # source files
OBJS = $(SRCS:.c=.o)

all: ${TARGET_EXEC} build

$(TARGET_EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build:
	$(shell mv $(PWD)/$(TARGET_EXEC) $(BUILD_DIR))

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	${RM} ${TARGET_EXEC} ${OBJS} $(SRCS:.c=.d)