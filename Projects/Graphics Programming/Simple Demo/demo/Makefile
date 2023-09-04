TARGET = texture
OBJS = main.o ../common/callbacks.o ../common/vram.o ../common/graphics.o

#INCDIR = ../../gu2gl/
CFLAGS = -Wall -std=c11
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Basic Texture

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak