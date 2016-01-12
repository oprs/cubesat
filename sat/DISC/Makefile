
SATDIR ?= $(TOPDIR)/sat
ARCH   ?= stm32f4

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./*/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*/*.cpp)) \
   $(patsubst %c,%o,$(wildcard ./*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./*.cpp))

OBJFILES := $(patsubst %cpp,%o,$(OBJFILES))

TARGETS = DISC.hex DISC.bin DISC.elf

CFLAGS += -I. $(APP_CFLAGS)
CFLAGS += -fdata-sections -ffunction-sections

LDFLAGS += -T$(SATDIR)/rules/arch-$(ARCH).ld
LDFLAGS += -Wl,-gc-sections
#LDFLAGS += -Wl,-Map=DISC.map
LDFLAGS += -specs=nosys.specs
LDFLAGS += -L$(SATDIR)/sys/ -lsystem

default: $(TARGETS)

DISC.hex: DISC.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O ihex $< $@

DISC.bin: DISC.elf
	@echo " [HEX] $@"
	$(QUIET) $(CP) -O binary $< $@

DISC.elf: $(OBJFILES)
	@echo " [ELF] $@"
	$(QUIET) $(CXX) $(MCUFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(TARGETS) $(OBJFILES)

flash: DISC.bin
	$(FLASH) write $< 0x08000000

.PHONY: default clean flash

include $(SATDIR)/rules/common.mk

