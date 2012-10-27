###############################################################################
#                                      Dawn Makefile [Pandora|Linux] Ver. 1.0 #
###############################################################################

TARGETDIR	= ../../Bin/$(PLATFORM)
OBJSDIR		= ../../Obj/$(PLATFORM)/$(BUILD)
SOURCEDIR	= Source

TARGET := Dawn

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

PREFIX = arm-angstrom-linux-gnueabi-

BUILD_PLATFORM	= PANDORA_LINUX
PLATFORM		= Pandora_Linux

CC = $(PREFIX)g++

CFLAGS_EXT =
ifeq ($(UNAME), Linux)
	CFLAGS_EXT	= -ffriend-injection -mcpu=cortex-a8 -Wa,-mcpu=cortex-a8 -mfpu=neon -Wa,-mfpu=neon -mfloat-abi=softfp
	SYSIPATH	= -I/usr/local/angstrom/arm/include
	SYSLPATH	= -L/usr/local/angstrom/arm/lib
	SYSLIBS		= -lX11 -lGLESv2 -lEGL -lrt -lc
endif

##### Debug #######
debug:		BUILD = Debug
debug:		ZED_BUILD = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CFLAGS = -c -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		ZED_LIBS = -lZEDRendererD -lZEDArithmeticD -lZEDSystemD
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	ZED_BUILD = RELEASE
release:	TARGET := $(TARGET)
release:	CFLAGS = -c -O3 $(CFLAGS_EXT)
release:	ZED_LIBS = -lZEDRenderer -lZEDArithmetic -lZEDSystem
release:	$(TARGET)

##### Profile #####
profile:	BUILD = Profile
profile:	ZED_BUILD = PROFILE
profile:	TARGET := $(TARGET)P
profile:	CFLAGS = -c -O3 -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
profile:	ZED_LIBS = -lZEDRendererP -lZEDArithmeticP -lZEDSystemP
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(notdir $(CURDIR)))

$(TARGETDIR):
	-mkdir -p $(TARGETDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))

###############
OBJS	= $(CPPFILES:.cpp=.o)
HEADERS	= $(wildcard *.hpp)
###############

$(TARGET): $(OBJS) $(TARGETDIR)
	-mkdir -p $(OBJSDIR)
	cd $(OBJSDIR) && $(CC) -o ../$(TARGETDIR)/$(TARGET) $(OBJS) -L$(ZEDPATH)/lib/$(PLATFORM) -Wl,-rpath,$(SYSLPATH) $(ZED_LIBS) $(SYSLIBS)

%.o: $(SOURCEDIR)/%.cpp
	-mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -DSUPPORT_X11 -DZED_BUILD_$(ZED_BUILD) -DZED_PLATFORM_$(BUILD_PLATFORM) -IHeaders -I$(ZEDPATH)/include/$(PLATFORM) $(SYSIPATH) $< -o $(OBJSDIR)/$@

endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

