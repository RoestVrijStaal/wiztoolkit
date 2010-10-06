# required
OPENWIZSDK	= /home/sharek/arm-openwiz-linux-gnu

# wiz specific
TARGET_BIN	= wizToolkit
TARGET_GCC	= $(OPENWIZSDK)/bin/arm-openwiz-linux-gnu-gcc
TARGET_AR	= $(OPENWIZSDK)/bin/arm-openwiz-linux-gnu-ar
TARGET_CFLAGS	= -Wall -DWIZ -fPIC -I/home/sharek/arm-openwiz-linux-gnu/include
TARGET_LIBS	= -lSDL -liconv -lSDL_ttf -lfreetype -L$(OPENWIZSDK)/arm-openwiz-linux-gnu/lib -L$(OPENWIZSDK)/lib 

# host machine version
HOST_BIN	= wizToolkitx86
HOST_GCC	= gcc
HOST_AR		= ar
HOST_CFLAGS	= -Wall -g -D_DEBUG -fPIC
HOST_LIBS	= -lSDL -lSDL_ttf -lfreetype

all:	target host
clean:
	rm lib$(HOST_BIN).so lib$(TARGET_BIN).so lib$(HOST_BIN).a lib$(TARGET_BIN).a *.o
target:
	# shared part
	$(TARGET_GCC) $(TARGET_CFLAGS) -c main.c
	$(TARGET_GCC) $(TARGET_CFLAGS) $(TARGET_LIBS) -shared -Wl,-soname=lib$(TARGET_BIN).so main.o -o lib$(TARGET_BIN).so
	# static part
	$(TARGET_AR) rcs lib$(TARGET_BIN).a main.o
host:
	# shared part
	$(HOST_GCC) $(HOST_CFLAGS) -c main.c
	$(HOST_GCC) $(HOST_CFLAGS) $(HOST_LIBS) -shared -Wl,-soname=lib$(HOST_BIN).so main.o -o lib$(HOST_BIN).so
	# static part
	$(HOST_AR) rcs lib$(HOST_BIN).a main.o

