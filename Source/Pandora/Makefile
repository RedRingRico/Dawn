###############################################################################
#                                      Dawn Makefile [Pandora|Linux] Ver. 1.0 #
###############################################################################

##### Make sure that the Angstrom ARM toolchain root was defined ##############
ifeq ($(strip $(PNDSDK)),)
$(error Please set PNDSDK to point to your Pandora toolchain root directory  )
endif

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/Pandora
export OBJSDIR		= $(TOPDIR)/Obj/Pandora/$(GCCVER)/$(BUILD)
endif
SOURCEDIR	= Source ../Common/Source ../Common/Source/OGLES2

TARGET := Dawn
OUTFILE	= $(TARGETDIR)/$(TARGET)
TOOLCHAIN_BIN = $(PNDSDK)/bin
TOOLCHAIN_USR = $(PNDSDK)/usr

# Get the machine type to determine which set of libraries to use
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

PREFIX = pandora-

BUILD_PLATFORM	= PANDORA
PLATFORM		= Pandora
ARCH			= ARM
BITTYPE			= 32

GCCVER	= $(shell $(CPP) -dumpversion)

BUILD_TYPE := debug

CPP = $(PREFIX)g++

CPPFLAGS	= -DBUILD_$(BUILD_DEF) -DPLATFORM_$(BUILD_PLATFORM) -DSUPPORT_X11 -I$(TOPSRC)/Pandora/Headers -I$(TOPSRC)/Common/Headers
CPPFLAGS_EXT =
CPPFLAGS_EXT	= -ffriend-injection -std=c++0x -mcpu=cortex-a8 -Wa,-mcpu=cortex-a8 -mfpu=neon -Wa,-mfpu=neon -mfloat-abi=softfp
SYSIPATH	= -idirafter $(PNDSDK)/usr/include
SYSLPATH	= -L$(PNDSDK)/usr/lib
SYSLIBS		= -lX11 -lGLESv2 -lEGL -lrt -lc -lIMGegl -lXau -lXdmcp -lsrv_um

##### Debug #######
debug:		BUILD = Debug
debug:		BUILD_DEF = DEBUG
debug:		TARGET := $(TARGET)D
debug:		CPPFLAGS += -c -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug:		$(TARGET)

##### Release #####
release:	BUILD = Release
release:	BUILD_DEF = RELEASE
release:	TARGET := $(TARGET)
release:	CPPFLAGS += -c -O3 $(CPPFLAGS_EXT)
release:	$(TARGET)

##### Profile #####
profile:	BUILD = Profile
profile:	BUILD_DEF = PROFILE
profile:	TARGET := $(TARGET)P
profile:	CPPFLAGS += -c -O3 -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(CURDIR))

VERSIONINFO:
	@printf "%s" "------------------------- Generating Version Information ---"
	@printf "%s\n" "-------------------"
	@sh ./GitVersion.sh ./Headers/GitVersion.hpp
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		:= $(CPPFILES:.cpp=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime $(MAKE) \
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Pandora/Makefile \
	$(BUILD_TYPE)
	@printf "\n%s" "----------------------------------------------------------"
	@printf "%s\n" "---------------------"
	@printf "Compile time: "
	@cat $(OBJSDIR)/compiletime
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

else

##### In the intermediate build directory #####################################

$(TARGET): $(OBJS)
	@printf "\n\n%s" "------------------------- MESSAGES FROM THE COMPILER ---"
	@printf "%s\n" "-----------------------"
	@cat *.cmsgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating: $(OUTFILE)... "
	@$(CPP) -o $(OUTFILE) $(OBJS) $(SYSLPATH) $(SYSLIBS) 2> lmsgs
	@printf "[OK]\n"

%.o: %.cpp
	@printf "Compiling: $<... "
	@$(CPP) -MMD -MP -MF $*.d $(CPPFLAGS)  $(SYSIPATH) $< -o $@ 2> $*.cmsgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "--------------------------------- ERROR -----------";\
		printf "%s\n" "----------------------------";\
		cat $*.msgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

-include $(OBJSDIR)/*.d

endif

.PHONY: clean
clean:
	@printf "Removing files from: $(TARGETDIR)... "
	@cd $(TARGETDIR) && rm -f ./*
	@printf "[OK]\n"
	@printf "Removing files from: $(OBJSDIR)... "
	@cd $(OBJSDIR) && rm -rf ./*
	@printf "[OK]\n"

