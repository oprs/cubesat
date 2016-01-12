
ARCH   ?= stm32f4
TOPDIR ?= $(CURDIR)

default: ODB ADCS DISC

doc:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) doc

check:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) check

clean:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) clean

tags:
	find . -type f \( -name "*.[ch]" -o -name "*.cpp" \) -print0 | xargs -0 ctags

ODB ADCS DISC:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) $@

flashODB flashADCS flashDISC:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) $@

cleanODB cleanADCS cleanDISC:
	@$(MAKE) -C $(TOPDIR)/sat TOPDIR=$(TOPDIR) $@

.PHONY: default doc check clean tags
.PHONY: ODB ADCS DISC
.PHONY: flashODB flashADCS flashDISC
.PHONY: cleanODB cleanADCS cleanDISC
