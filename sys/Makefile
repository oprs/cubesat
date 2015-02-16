
ARCHIVE = libsystem.a

OBJ_ARCH = \
   $(patsubst %s,%o,$(wildcard ./$(ARCH)/src/*.s)) \
   $(patsubst %c,%o,$(wildcard ./$(ARCH)/src/*.c)) \
   $(patsubst %c,%o,$(wildcard ./$(ARCH)/src/peripherals/*.c))

OBJ_RTOS = \
   $(patsubst %c,%o,$(wildcard ./FreeRTOS/*.c)) \
   $(patsubst %c,%o,$(wildcard ./FreeRTOS/portable/MemMang/heap_3.c)) \
   $(patsubst %c,%o,$(wildcard ./FreeRTOS/portable/$(ARCH)/*.c)) \
   $(patsubst %c,%o,$(wildcard ./sys/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./sys/*.cpp))

OBJ_DEVICE = \
   $(patsubst %c,%o,$(wildcard ./src/device/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./src/device/*.cpp))

OBJ_BASE = \
   $(patsubst %c,%o,$(wildcard ./src/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./src/*.cpp))

OBJFILES = $(OBJ_ARCH) $(OBJ_RTOS) $(OBJ_DEVICE) $(OBJ_BASE)

$(OBJ_ARCH):   CFLAGS += $(ARCH_CFLAGS)
$(OBJ_RTOS):   CFLAGS += -I./inc $(RTOS_CFLAGS)
$(OBJ_DEVICE): CFLAGS += -I. -I./inc $(ARCH_CFLAGS) $(RTOS_CFLAGS)
$(OBJ_BASE):   CFLAGS += -I. -I./inc $(ARCH_CFLAGS) $(RTOS_CFLAGS)

default: $(ARCHIVE)

clean:
	$(RM) $(ARCHIVE) $(OBJFILES)

include $(TOPDIR)/rules/common.mk

