
ARCHIVE = libuser.a

OBJFILES = \
   $(patsubst %c,%o,$(wildcard ./src/*.c)) \
   $(patsubst %cpp,%o,$(wildcard ./src/*.cpp))

CFLAGS += -I./inc $(APP_CFLAGS)

default: $(ARCHIVE)

clean:
	$(RM) $(ARCHIVE) $(OBJFILES)

include $(TOPDIR)/rules/common.mk

