
SATDIR ?= $(TOPDIR)/sat
ARCH   ?= stm32f4

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./*/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*/*.cpp)) \
   $(patsubst %c,%o,$(wildcard ./*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*.cpp)) \
   $(patsubst %c,%o,$(wildcard ./lib/armadillo/src/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./lib/armadillo/src/*.cpp))

TARGETS = ADCS.hex ADCS.elf

CFLAGS += -I. $(APP_CFLAGS)
CFLAGS += -I./lib/armadillo/include
CFLAGS += -fdata-sections -ffunction-sections

LDFLAGS += -T$(SATDIR)/rules/arch-$(ARCH).ld
LDFLAGS += -Wl,-gc-sections
#LDFLAGS += -Wl,-Map=ADCS.map
LDFLAGS += -specs=nosys.specs
LDFLAGS += -L$(SATDIR)/sys/ -lsystem

ADCS.hex: ADCS.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O ihex $< $@

ADCS.elf: $(OBJFILES)
	@echo " [ELF] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -o $@ $^ $(LDFLAGS)

default: $(OBJFILES)

clean:
	$(RM) $(TARGETS) $(OBJFILES)

.PHONY: $(TARGETS) default clean

include $(SATDIR)/rules/common.mk

