
ARCH   ?= stm32f4
SATDIR ?= $(TOPDIR)/sat

SUB_SYS  = $(SATDIR)/sys
SUB_ODB  = $(SATDIR)/ODB
SUB_ADCS = $(SATDIR)/ADCS

SUB_APP = \
 $(SATDIR)/app/examples/blinky \
 $(SATDIR)/app/examples/extmem

SUB_ALL = $(SUB_SYS) $(SUB_ODB) $(SUB_ADCS) $(SUB_APP)
SUB_CLN = $(addsuffix .clean,$(SUB_ALL))

all: $(SUB_ODB) $(SUB_ADCS)

$(SUB_ODB): $(SUB_SYS)

$(SUB_ADCS): $(SUB_SYS)

$(SUB_APP): $(SUB_SYS)

$(SUB_APP): $(SUB_SYS)

$(SUB_ALL):
	@$(MAKE) -C $@ SATDIR=$(SATDIR) ARCH=$(ARCH)

check:
	$(CHECK) -I. -I$(SATDIR)/sys/inc -I$(SATDIR)/sys/inc/device -I$(SATDIR)/sys/inc/system ./sys/src ./app

clean: $(SUB_CLN)

$(SUB_CLN): %.clean:
	@$(MAKE) -C $* SATDIR=$(SATDIR) ARCH=$(ARCH) clean

doc:
	doxygen $(SATDIR)/rules/Doxyfile


.PHONY: all check clean doc $(SUB_ALL)

include $(SATDIR)/rules/common.mk

