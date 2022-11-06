prefix = .
OPT = -O3 -flto

includedir = $(prefix)/include

libdir = $(prefix)/lib
target = $(libdir)/libserialib.a

# use gcc-ar for LTO support
AR = gcc-ar

ifeq '$(findstring sh,$(SHELL))' 'sh'
# UNIX, MSYS2 or Cygwin
MKDIR = mkdir -p
CP = cp
RM = rm -f
RMDIR = rm -f -r
else
# Windows, neither MSYS2 nor Cygwin
MKDIR = mkdir
CP = copy
RM = del /Q
RMDIR = rmdir /S /Q
endif

CXXFLAGS = -I$(includedir) $(OPT)

headers = $(includedir)/serialib.h
objects = serialib.o

$(target): $(headers) $(objects) $(libdir)
	$(AR) rcs $@ $(objects)

$(libdir):
	-$(MKDIR) $@

$(includedir):
	-$(MKDIR) $@

$(includedir)/%.h: $(includedir) %.h
	$(CP) $(@F) $<

.PHONY: clean
clean:
	-$(RM) *.o
