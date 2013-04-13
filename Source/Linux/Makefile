###############################################################################
#                                          Dawn Makefile [Linux x86] Ver. 1.0 #
###############################################################################

ifeq ($(strip $(ZEDSDK)),)
$(error Please set ZEDSDK to point to your ZED SDK root directory )
endif

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/$(PLATFORM)
export OBJSDIR		= $(TOPDIR)/Obj/$(PLATFORM)/$(GCCVER)/$(BUILD)
endif
SOURCEDIR	= Source ../Common/Source
#../Common/Source/OGLES2

TARGET := Dawn
OUTFILE	=	$(TARGETDIR)/$(TARGET)_$(GCCVER)

PLATFORM		:= Linux
BUILD_PLATFORM	:= LINUX
BUILD_ARCH		:= X86
ARCH			:= x86
BITSIZE			:= 32

GCCVER	= $(shell $(CPP) -dumpversion)

BUILD_TYPE := debug

32BIT ?= False
64BIT ?= False

##### Get the machine type to determine which set of libraries to use #########
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

ifeq ($(UNAME), Linux)
	CPPFLAGS_EXT	= -ffriend-injection -std=gnu++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		= -lX11 -lGL -lrt
	LINKFLAGS	=
##### Check for forced 32-bit or 64-bit builds ################################
ifneq ($(64BIT), False)
	CPPFLAGS_EXT	+=	-m64
	ARCH		=	x86
	BITSIZE		=	64
else
ifneq ($(32BIT), False)
	CPPFLAGS_EXT	+=	-m32
	ARCH		= x86
	BITSIZE		= 32
else
##### Nothing forced.  Use what the machine reports ###########################
ifeq ($(UNAME_MACHINE), x86_64)
	CPPFLAGS_EXT	+=	-m64
	ARCH		=	x86
	BITSIZE		=	64
endif
ifeq ($(UNAME_MACHINE), i686)
	CPPFLAGS_EXT	+=	-m32
	ARCH		= x86
	BITSIZE		= 32
endif
endif
endif
endif

CPP = g++

CPPFLAGS	=	-c -DZED_BUILD_$(BUILD_DEF) -DZED_PLATFORM_$(BUILD_PLATFORM) \
				-DZED_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH) \
				-DZED_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH)_$(BITSIZE) \
				-DZED_BITSIZE_$(BITSIZE) -DZED_ARCH_$(BUILD_ARCH) \
				-I$(TOPSRC)/Linux/Headers -I$(TOPSRC)/Common/Headers
CPPFLAGS_EXT=	-ffriend-injection -std=c++0x
SYSIPATH	=	-idirafter $(PNDSDK)/usr/include
INCPATH		=	-I$(ZEDSDK)/include/Linux
SYSLPATH	=	
#-L$(PNDSDK)/usr/lib
LIBPATH		=	-L$(ZEDSDK)/lib/Linux/$(ARCH)/$(BITSIZE)
SYSLIBS		=	-lX11 -lGL -lXrandr -lrt -pthread
LINKFLAGS	=

##### Debug #######
debug:		BUILD		= Debug
debug:		BUILD_TYPE	= debug
debug:		BUILD_DEF	= DEBUG
debug:		TARGET := $(TARGET)D
debug:		CPPFLAGS += -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug:		LIBS = -lZEDRendererD -lZEDArithmeticD -lZEDSystemD
debug:		$(TARGET)

##### Release #####
release:	BUILD		= Release
release:	BUILD_TYPE	= release
release:	BUILD_DEF	= RELEASE
release:	TARGET := $(TARGET)
release:	CPPFLAGS += -O3 $(CPPFLAGS_EXT)
release:	LINKFLAGS += -Wl,-S
release:	$(TARGET)

##### Profile #####
profile:	BUILD		= Profile
profile:	BUILD_TYPE	= profile
profile:	BUILD_DEF	= PROFILE
profile:	TARGET := $(TARGET)P
profile:	CPPFLAGS += -O3 -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
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
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Linux/Makefile \
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
	@$(CPP) -o $(OUTFILE) $(LINKFLAGS) $(OBJS) $(SYSLPATH) $(LIBPATH) \
	$(LIBS) $(SYSLIBS) 2> lmsgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "------------------------------------ ERROR --------";\
		printf "%s\n" "----------------------------";\
		cat lmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n" "------------------------";\
		exit 1;\
	fi

%.o: %.cpp
	@printf "Compiling: $<... "
	@$(CPP) -MMD -MP -MF $*.d $(CPPFLAGS) $(SYSIPATH) $(INCPATH) \
	$< -o $@ 2> $*.cmsgs;\
	RETVAL=$$?;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "--------------------------------- ERROR -----------";\
		printf "%s\n" "----------------------------";\
		cat $*.cmsgs;\
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

