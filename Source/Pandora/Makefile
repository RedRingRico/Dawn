###############################################################################
#                                      Dawn Makefile [Pandora|Linux] Ver. 1.0 #
###############################################################################

##### Make sure that the Angstrom ARM toolchain root was defined ##############
ifeq ($(strip $(PNDSDK)),)
$(error Please set PNDSDK to point to your Pandora toolchain root directory  )
endif

TARGETDIR	= ../../Bin/$(PLATFORM)
OBJSDIR		= ../../Obj/$(PLATFORM)/$(BUILD)
SOURCEDIR	= Source

TARGET := Dawn
TOOLCHAIN_BIN = $(PNDSDK)/bin
TOOLCHAIN_USR = $(PNDSDK)/usr

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

PREFIX = pandora-

BUILD_PLATFORM	= PANDORA
PLATFORM		= Pandora

CC = $(PREFIX)g++

CFLAGS_EXT =
ifeq ($(UNAME), Linux)
	CFLAGS_EXT	= -ffriend-injection -std=c++0x -mcpu=cortex-a8 -Wa,-mcpu=cortex-a8 -mfpu=neon -Wa,-mfpu=neon -mfloat-abi=softfp
	SYSIPATH	= -idirafter $(PNDSDK)/usr/include
	SYSLPATH	= -L$(PNDSDK)/usr/lib
	SYSLIBS		= -lX11 -lGLESv2 -lEGL -lrt -lc -lIMGegl -lXau -lXdmcp -lsrv_um
endif

##### Debug #######
debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CFLAGS = -c -g -ggdb -Wall -D_DEBUG $(CFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUILD_DEF = RELEASE
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

.PHONY: VERSIONINFO OBJSDIR TARGETDIR
VERSIONINFO:
	@echo "---------------------- Generating Version Information -------------------------"
	@sh ./GitVersion.sh ./Headers/GitVersion.hpp
	@echo "-------------------------------------------------------------------------------"

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
COMFILES	:= $(foreach dir,../Common/Source,$(notdir $(wildcard $(dir)/*.cpp)))
GLESFILES	:= $(foreach dir,../Common/Source/OGLES2,$(notdir $(wildcard $(dir)/*.cpp)))

###############
OBJS		= $(CPPFILES:.cpp=.o)
COBJS		= $(COMFILES:.cpp=.o)
GLESOBJS	= $(GLESFILES:.cpp=.o)
HEADERS		= $(wildcard *.hpp)
###############

$(TARGET): VERSIONINFO OBJSDIR TARGETDIR $(OBJS) $(GLESOBJS) $(COBJS)
	cd $(OBJSDIR) && $(CC) -o ../$(TARGETDIR)/$(TARGET) $(OBJS) $(GLESOBJS) $(COBJS) $(SYSLPATH) $(SYSLIBS)

%.o: ../Common/Source/OGLES2/%.cpp
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

%.o: ../Common/Source/%.cpp
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@

%.o: $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -IHeaders -I../Common/Headers $(SYSIPATH) $< -o $(OBJSDIR)/$@


endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

