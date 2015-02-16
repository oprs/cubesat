
ARCH   ?= stm32f4
TOPDIR  = $(CURDIR)

SUB_SYS = ./sys
SUB_LIB = ./lib/user
SUB_APP = \
 ./app/examples/blinky \
 ./app/examples/extmem

SUB_ALL = $(SUB_LIB) $(SUB_SYS) $(SUB_APP)
SUB_CLN = $(addsuffix .clean,$(SUB_ALL))

all: $(SUB_APP)

$(SUB_APP): $(SUB_LIB)
$(SUB_LIB): $(SUB_SYS)

$(SUB_ALL):
	@$(MAKE) -C $@ TOPDIR=$(TOPDIR) ARCH=$(ARCH)

clean: $(SUB_CLN)

$(SUB_CLN): %.clean:
	@$(MAKE) -C $* TOPDIR=$(TOPDIR) ARCH=$(ARCH) clean

tags:
	find . -type f \( -name "*.[ch]" -o -name "*.cpp" \) -print | xargs ctags


.PHONY: all clean tags $(SUB_ALL)

include ./rules/common.mk

