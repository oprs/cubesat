
ARCH   ?= stm32f4
TOPDIR ?= $(CURDIR)

default: sat

sat:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR)

clean:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) clean


.PHONY: sat

