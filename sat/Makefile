
ARCH   ?= stm32f4
SATDIR ?= $(TOPDIR)/sat

SUB_SYS = $(SATDIR)/sys
SUB_APP = \
 $(SATDIR)/app/examples/blinky \
 $(SATDIR)/app/examples/extmem

SUB_ALL = $(SUB_SYS) $(SUB_APP)
SUB_CLN = $(addsuffix .clean,$(SUB_ALL))

all: $(SUB_APP)

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

tags:
	find . -type f \( -name "*.[ch]" -o -name "*.cpp" \) -print0 | xargs -0 ctags


.PHONY: all check clean doc tags $(SUB_ALL)

include $(SATDIR)/rules/common.mk

