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

BUILD_PLATFORM	= PANDORA
PLATFORM		= Pandora

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
debug:		BUILD_DEF = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CFLAGS = -c -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUID_DEF = RELEASE
release:	TARGET := $(TARGET)
release:	CFLAGS = -c -O3 $(CFLAGS_EXT)
release:	$(TARGET)

##### Profile #####
profile:	BUILD = Profile
profile:	BUILD_DEF = PROFILE
profile:	TARGET := $(TARGET)P
profile:	CFLAGS = -c -O3 -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(notdir $(CURDIR)))

$(TARGETDIR):
	-mkdir -p $(TARGETDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
COMFILES	:= $(foreach dir,../Common/Source,$(notdir $(wildcard $(dir)/*.cpp)))
GLESFILES	:= $(foreach dir,../Common/Source/OGLES2,$(notdir $(wildcard $(dir)/*.cpp)))

###############
OBJS		= $(CPPFILES:.cpp=.o)
COBJS		= $(COMFILES:.cpp=.o)
GLESOBJS	= $(GLESFILES:.cpp=.o)
HEADERS		= $(wildcard *.hpp)
###############

$(TARGET): $(OBJS) $(GLESOBJS) $(COBJS) $(TARGETDIR)
	-mkdir -p $(OBJSDIR)
	cd $(OBJSDIR) && $(CC) -o ../$(TARGETDIR)/$(TARGET) $(OBJS) $(GLESOBJS) $(COBJS) -Wl,-rpath,$(SYSLPATH) $(SYSLIBS)

%.o: ../Common/Source/OGLES2/%.cpp
	-mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

%.o: ../Common/Source/%.cpp
	-mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

%.o: $(SOURCEDIR)/%.cpp
	-mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

