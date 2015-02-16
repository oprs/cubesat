
TOPDIR ?= ../../..
ARCH   ?= stm32f4

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*.cpp))

TARGETS = main.hex main.elf

CFLAGS += -I. $(APP_CFLAGS)

LDFLAGS += -T$(TOPDIR)/rules/arch-$(ARCH).ld
LDFLAGS += -L$(TOPDIR)/sys/ -lsystem
LDFLAGS += --specs=nosys.specs


main.hex: main.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O ihex $< $@

main.elf: $(OBJFILES)
	@echo " [ELF] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -o $@ $^ $(LDFLAGS)

default: $(OBJFILES)

clean:
	$(RM) $(TARGETS) $(OBJFILES)

.PHONY: $(TARGETS) default clean

include $(TOPDIR)/rules/common.mk

