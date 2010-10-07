# required
OPENWIZSDK	= /home/sharek/arm-openwiz-linux-gnu

# wiz specific
TARGET_BIN	= wizToolkitSample1
TARGET_GCC	= $(OPENWIZSDK)/bin/arm-openwiz-linux-gnu-gcc
TARGET_AR	= $(OPENWIZSDK)/bin/arm-openwiz-linux-gnu-ar
TARGET_CFLAGS	= -Wall -DWIZ -I/home/sharek/arm-openwiz-linux-gnu/include
TARGET_LIBS	= -lSDL -liconv -lSDL_ttf -lSDL_image -lfreetype -L$(OPENWIZSDK)/arm-openwiz-linux-gnu/lib -L$(OPENWIZSDK)/lib 

# host machine version
HOST_BIN	= wizToolkitSample1x86
HOST_GCC	= gcc
HOST_AR		= ar
HOST_CFLAGS	= -Wall -g -D_DEBUG
HOST_LIBS	= -lSDL -lSDL_ttf -lfreetype -lSDL_image 

all:	build_lib target host
clean:
	rm $(HOST_BIN).bin $(TARGET_BIN).gpe
build_lib:
	make -C ../lib
target:
	$(TARGET_GCC) $(TARGET_CFLAGS) $(TARGET_LIBS) main.c -L../lib -lwizToolkit    -o $(TARGET_BIN).gpe
host:
	$(HOST_GCC)   $(HOST_CFLAGS)   $(HOST_LIBS)   main.c -L../lib -lwizToolkitx86 -o $(HOST_BIN).bin

