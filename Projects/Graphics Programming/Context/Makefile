TARGET = context
OBJS = context.o ../common/callbacks.o

#INCDIR = ../../gu2gl/
CFLAGS = -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Basic Context

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak