
# fallback target: called when no target was defined in the parent Makefile

fallback:
	$(error "no target found in Makefile")


include $(SATDIR)/rules/arch-$(ARCH).mk

RM     := rm -f
CHECK  := cppcheck --enable=all
#CHECK  := cppcheck --force --enable=warning,style
FLASH  := st-flash

CFLAGS += -Wall -Wextra
CFLAGS += -DARCH=$(ARCH)

ifdef DEBUG
#CFLAGS += -g -O0 -DDEBUG -fstack-usage
 CFLAGS += -g -O0 -DDEBUG
else
 CFLAGS += -Os
endif

ifndef VERBOSE
 QUIET := @
endif

RTOS_CFLAGS  = -I$(SATDIR)/sys/FreeRTOS/include
RTOS_CFLAGS += -I$(SATDIR)/sys/FreeRTOS/portable/$(ARCH)

APP_CFLAGS   = $(ARCH_CFLAGS) $(RTOS_CFLAGS)
APP_CFLAGS  += -I$(SATDIR)
APP_CFLAGS  += -I$(SATDIR)/sys
APP_CFLAGS  += -I$(SATDIR)/sys/system
APP_CFLAGS  += -I$(SATDIR)/sys/device

$(SUBDIRS):
	@$(MAKE) -C $@ TOPDIR=$(TOPDIR) ARCH=$(ARCH)

SUBCLEAN := $(addsuffix .clean,$(SUBDIRS))

subclean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	@$(MAKE) -C $* TOPDIR=$(TOPDIR) ARCH=$(ARCH) clean

.PHONY: $(SUBDIRS) $(SUBCLEAN) fallback subclean


%.o: %.c
	@echo "  [CC] $@"
	$(QUIET) $(CC) $(MCUFLAGS) $(CFLAGS) -Wstrict-prototypes -o $@ -c $<

%.o: %.cc
	@echo " [CXX] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -std=c++11 $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	@echo " [CXX] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -std=c++11 $(CFLAGS) -o $@ -c $<

%.o: %.s
	@echo "  [AS] $@"
	$(QUIET) $(AS) $(MCUFLAGS) -o $@ -c $<

$(ARCHIVE): $(OBJFILES)
	@echo "  [AR] $@"
	$(QUIET) $(AR) $@ $(OBJFILES)

