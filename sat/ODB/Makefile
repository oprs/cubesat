
SATDIR ?= $(TOPDIR)/sat
ARCH   ?= stm32f4

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./*/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*/*.cpp))

TARGETS = ODB.hex ODB.elf

CFLAGS += -I. $(APP_CFLAGS)
CFLAGS += -fdata-sections -ffunction-sections

LDFLAGS += -T$(SATDIR)/rules/arch-$(ARCH).ld
LDFLAGS += -Wl,-gc-sections
#LDFLAGS += -Wl,-Map=ODB.map
LDFLAGS += -specs=nosys.specs
LDFLAGS += -L$(SATDIR)/sys/ -lsystem

ODB.hex: ODB.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O ihex $< $@

ODB.elf: $(OBJFILES)
	@echo " [ELF] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -o $@ $^ $(LDFLAGS)

default: $(OBJFILES)

clean:
	$(RM) $(TARGETS) $(OBJFILES)

.PHONY: $(TARGETS) default clean

include $(SATDIR)/rules/common.mk

