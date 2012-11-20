# -------------------------------------------------------------------------------------------------------------
# -- build options
# -------------------------------------------------------------------------------------------------------------

BINARY = cgamei386

SRC_FILES = $(shell ls *.c)
HDR_FILES = $(shell ls *.h)

SVN_VERSION=$(shell svnversion)

DATE=$(shell date +%F)
HOUR=$(shell date +%H)
MIN=$(shell date +%M)
COMPILE_DATE="$(DATE) $(HOUR):$(MIN) CET"
CC=gcc

BASE_CFLAGS=-pipe -Wall -pedantic

BROOT=linux
BR=$(BROOT)/release
BD=$(BROOT)/debug

OBJR_Q3A=$(SRC_FILES:%.c=$(BR)$(B_Q3A)/%.o)
OBJD_Q3A=$(SRC_FILES:%.c=$(BD)$(B_Q3A)/%.o)

DEBUG_DEFINES=-DSVN_VERSION=\"$(SVN_VERSION)\" -DCOMPILE_DATE=\"$(COMPILE_DATE)\"
RELEASE_DEFINES=-DSVN_VERSION=\"$(SVN_VERSION)\" -DCOMPILE_DATE=\"$(COMPILE_DATE)\"

DEBUG_CFLAGS=$(BASE_CFLAGS) -ggdb -g -pg $(DEBUG_DEFINES) -I/usr/include/libxml2
RELEASE_CFLAGS=$(BASE_CFLAGS) -Os $(RELEASE_DEFINES) -I/usr/include/libxml2

# if we on 64bit system...

ifeq ($(shell uname -m),x86_64)
    DEBUG_DEFINES += -m32
    RELEASE_DEFINES += -m32
endif


SHLIBCFLAGS=-fPIC -std=c99
SHLIBLDFLAGS=-Wl,--no-undefined -shared -Wl
EXTLIBS = -lm -lxml2 

# -------------------------------------------------------------------------------------------------------------
# -- build rules
# -------------------------------------------------------------------------------------------------------------

release: banner $(BR)/$(BINARY).so
debug: banner $(BD)/$(BINARY).so
all: banner release




# -------------------------------------------------------------------------------------------------------------
# -- optional build
# -------------------------------------------------------------------------------------------------------------

banner:
	@printf "\n"
	@printf "\033\13301;31mmDd \033\13301;33mRS Makefile  (rev-$(SVN_VERSION)) (%s)\n" $(COMPILE_DATE)
	@printf "\n\033\13301;32m----------------------------------------------------------\n\033\13300;39m"

clean:
	@rm -rf $(BD)$(B_Q3A) $(BR)$(B_Q3A) $(BD)$(B_JK2) $(BR)$(B_JK2)




# -------------------------------------------------------------------------------------------------------------
# -- release build
# -------------------------------------------------------------------------------------------------------------

$(BR)/$(BINARY).so: $(BR) $(OBJR_Q3A)
	@printf "\n"
	@printf "\033\13301;32m->\033\13301;37m linking to $(BR)$(B_Q3A)/$(BINARY).so\n\033\13300;39m"
	$(CC) $(RELEASE_CFLAGS) $(SHLIBLDFLAGS) -o $@ $(OBJR_Q3A) -lxml2
	@printf "\033\13301;32m->\033\13301;37m stripping $(BR)$(B_Q3A)/$(BINARY).so\n\033\13300;39m"
	strip $(BR)/$(BINARY).so

$(BR)/%.o: %.c $(HDR_FILES)
	@printf "R \033\13301;33m-\033\13301;37m %-20s %s\033\13300;39m\n" $< $@
	$(CC) $(INCLUDES) $(RELEASE_CFLAGS) $(RELEASE_DEFINES) $(SHLIBCFLAGS) -o $@  -c $<

$(BR):
	@if [ ! -d $(BROOT) ];then mkdir $(BROOT);fi
	@if [ ! -d $(@) ];then mkdir $@;fi



# -------------------------------------------------------------------------------------------------------------
# -- debug build
# -------------------------------------------------------------------------------------------------------------

$(BD)/$(BINARY).so: $(BD) $(OBJD_Q3A)
	@printf "\n"
	@printf "\033\13301;32m->\033\13301;37m linking to $(BD)/$(BINARY).so\n\033\13300;39m"
	$(CC) $(DEBUG_CFLAGS) $(SHLIBLDFLAGS) -o $@ $(EXTLIBS) $(OBJD_Q3A)


$(BD)/%.o: %.c $(HDR_FILES)
	@printf "D \033\13301;33m-\033\13301;37m %-20s %s\033\13300;39m\n" $< $@
	$(CC) $(INCLUDES) $(DEBUG_DEFINES) $(SHLIBCFLAGS) -o $@ -c $<

$(BD):
	@if [ ! -d $(BROOT) ];then mkdir $(BROOT);fi
	@if [ ! -d $(@) ];then mkdir $@;fi

