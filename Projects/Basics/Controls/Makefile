TARGET = controls
OBJS = main.o

# Define to build this as a prx (instead of a static elf)
#BUILD_PRX=1
# Define the name of our custom exports (minus the .exp extension)
#PRX_EXPORTS=exports.exp


INCDIR = 
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Controls Example

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak