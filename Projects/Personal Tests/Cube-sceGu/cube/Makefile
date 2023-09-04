TARGET = cube
OBJS = cube.o ../common/callbacks.o ../common/vram.o ../common/graphics.o

#INCDIR = ../../gu2gl/
CFLAGS = -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Basic Cube

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak