
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

tags:
	find . -type f \( -name "*.[ch]" -o -name "*.cpp" \) -print0 | xargs -0 ctags

.PHONY: sat doc check clean tags


# Code::Blocks targets

Release:
	@$(MAKE) sat

Debug:
	@$(MAKE) sat DEBUG=1

cleanRelease:
	@$(MAKE) clean

cleanDebug:
	@$(MAKE) clean

.PHONY: Release Debug cleanRelease cleanDebug

