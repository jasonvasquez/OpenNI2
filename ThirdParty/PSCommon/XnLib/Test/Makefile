include ../../BuildSystem/CommonDefs.mak

BIN_DIR = ../Bin

INC_DIRS = \
	../Include \
	../../Testing

SRC_FILES = \
	*.cpp \
	Linux/*.cpp \
	../../Testing/gmock-gtest-all.cc

ifeq ("$(OSTYPE)","Darwin")
	INC_DIRS += /opt/local/include
	LIB_DIRS += /opt/local/lib
	LDFLAGS += -framework CoreFoundation -framework IOKit
endif

EXE_NAME = XnLibTest
USED_LIBS = XnLib usb-1.0 dl pthread
ifneq ("$(OSTYPE)","Darwin")
	USED_LIBS += rt 
endif
CFLAGS += -Wall

test: all
	$(OUTPUT_FILE)

include ../../BuildSystem/CommonCppMakefile
