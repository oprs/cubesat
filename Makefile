
ARCH   ?= stm32f4
TOPDIR ?= $(CURDIR)

default: sat

sat:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR)

doc:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) doc

check:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) check

clean:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) clean


.PHONY: sat doc check clean

