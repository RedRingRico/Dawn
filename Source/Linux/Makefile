###############################################################################
#                                          Dawn Makefile [Linux x86] Ver. 1.0 #
###############################################################################

TARGETDIR	= ../../Bin/$(PLATFORM)
OBJSDIR		= ../../Obj/$(PLATFORM)/$(BUILD)
SOURCEDIR	= Source

TARGET := Dawn

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

CC = g++

CFLAGS_EXT =
ifeq ($(UNAME), Linux)
	CFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		= -lX11 -lGL -lrt
ifeq ($(UNAME_MACHINE), x86_64)
	BUILD_PLATFORM	= LINUX64_X86
	PLATFORM		= Linux64_x86
endif
ifeq ($(UNAME_MACHINE), i686)
	BUILD_PLATFORM	= LINUX32_X86
	PLATFORM		= Linux32_x86
endif
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

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))

###############
OBJS	= $(CPPFILES:.cpp=.o)
HEADERS	= $(wildcard *.hpp)
###############

$(TARGET): $(OBJS) $(TARGETDIR)
	-mkdir -p $(OBJSDIR)
	cd $(OBJSDIR) && $(CC) -o ../$(TARGETDIR)/$(TARGET) $(OBJS) -L$(ZEDPATH)/lib/$(PLATFORM) $(ZED_LIBS) $(SYSLIBS)

%.o: $(SOURCEDIR)/%.cpp
	-mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -DZED_BUILD_$(ZED_BUILD) -DZED_PLATFORM_$(BUILD_PLATFORM) -IHeaders -I$(ZEDPATH)/include/$(PLATFORM) -I$(GLINCPATH) $(SYSIPATH) $< -o $(OBJSDIR)/$@

endif

.PHONY: clean
clean:
	cd $(TARGETDIR) && rm -f ./*
	cd $(OBJSDIR) && rm -rf ./*

