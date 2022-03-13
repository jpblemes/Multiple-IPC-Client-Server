PWD = $(shell pwd)
BUILD_DIR = $(PWD)/build
SHARED_DIR = $(PWD)/shared
#SUBDIRS = $(wildcard */.)

#Include libs
LIBS += libs/libipc_sockets
LIBS += libs/libipc_msgq
LIBS += libs/libsensors
#Include apps
APPS += apps/testServer
APPS += apps/testClient

ALL_DIRS = $(LIBS) $(APPS)

RM = rm -f   # rm command
RM_DIR = rm -rf# rm a filled dir command

all: dir $(LIBS) $(APPS)

dir:
	$(shell mkdir $(BUILD_DIR))
	$(shell mkdir $(SHARED_DIR))

$(LIBS):
	$(MAKE) -C $@

$(APPS):
	$(MAKE) -C $@

.PHONY: all $(ALL_DIRS)

SUBCLEAN = $(addsuffix .clean,$(ALL_DIRS))

clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
	$(RM_DIR) $(BUILD_DIR) $(SHARED_DIR)
	${RM} *.o *.d *.txt