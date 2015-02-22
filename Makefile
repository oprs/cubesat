
ARCH   ?= stm32f4
TOPDIR  = $(CURDIR)

SUB_SYS = ./sys
SUB_APP = \
 ./app/examples/blinky \
 ./app/examples/extmem

SUB_ALL = $(SUB_SYS) $(SUB_APP)
SUB_CLN = $(addsuffix .clean,$(SUB_ALL))

all: $(SUB_APP)

$(SUB_APP): $(SUB_SYS)

$(SUB_ALL):
	@$(MAKE) -C $@ TOPDIR=$(TOPDIR) ARCH=$(ARCH)

check:
	$(CHECK) -I. -I$(TOPDIR)/sys/inc -I$(TOPDIR)/sys/inc/device -I$(TOPDIR)/sys/inc/system ./sys/src ./app

clean: $(SUB_CLN)

$(SUB_CLN): %.clean:
	@$(MAKE) -C $* TOPDIR=$(TOPDIR) ARCH=$(ARCH) clean

doc:
	doxygen $(TOPDIR)/rules/Doxyfile

tags:
	find . -type f \( -name "*.[ch]" -o -name "*.cpp" \) -print0 | xargs -0 ctags


.PHONY: all check clean doc tags $(SUB_ALL)

include ./rules/common.mk

