
# fallback target: called when no target was defined in the parent Makefile

fallback:
	$(error "no target found in Makefile")


include $(TOPDIR)/rules/arch-$(ARCH).mk

RM := rm -f

CFLAGS += -Wall
CFLAGS += -DARCH=$(ARCH)

ifdef DEBUG
 CFLAGS += -g -O0 -DDEBUG
else
 CFLAGS += -Os
endif

ifndef VERBOSE
 QUIET := @
endif

RTOS_CFLAGS  = -I$(TOPDIR)/sys/FreeRTOS/include
RTOS_CFLAGS += -I$(TOPDIR)/sys/FreeRTOS/portable/$(ARCH)

APP_CFLAGS   = $(ARCH_CFLAGS) $(RTOS_CFLAGS)
APP_CFLAGS  += -I$(TOPDIR)/sys/inc
APP_CFLAGS  += -I$(TOPDIR)/lib/user/inc

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
	$(QUIET) $(AS) -o $@ -c $<

$(ARCHIVE): $(OBJFILES)
	@echo "  [AR] $@"
	$(QUIET) $(AR) $@ $(OBJFILES)

