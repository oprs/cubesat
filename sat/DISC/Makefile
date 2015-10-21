
SATDIR ?= $(TOPDIR)/sat
ARCH   ?= stm32f4

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./*/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*/*.cpp)) \
   $(patsubst %c,%o,$(wildcard ./*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*.cpp))

OBJFILES := $(patsubst %cpp,%o,$(OBJFILES))

TARGETS = DISC.hex DISC.elf

CFLAGS += -I. $(APP_CFLAGS)
CFLAGS += -fdata-sections -ffunction-sections

LDFLAGS += -T$(SATDIR)/rules/arch-$(ARCH).ld
LDFLAGS += -Wl,-gc-sections
#LDFLAGS += -Wl,-Map=DISC.map
LDFLAGS += -specs=nosys.specs
LDFLAGS += -L$(SATDIR)/sys/ -lsystem

DISC.hex: DISC.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O ihex $< $@

DISC.elf: $(OBJFILES)
	@echo " [ELF] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -o $@ $^ $(LDFLAGS)

default: $(OBJFILES)

clean:
	$(RM) $(TARGETS) $(OBJFILES)

.PHONY: $(TARGETS) default clean

include $(SATDIR)/rules/common.mk

