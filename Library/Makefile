#
#	Controller Area Network - Lawicel SLCAN Protocol (Serial-Line CAN)
#
#	Copyright (c) 2016-2024  Uwe Vogt, UV Software, Berlin (info@uv-software.com)
#	All rights reserved.
#
#	This file is part of SLCAN.
#
#	SLCAN is dual-licensed under the BSD 2-Clause "Simplified" License
#	and under the GNU General Public License v3.0 (or any later version). You can
#	choose between one of them if you use SLCAN in whole or in part.
#
#	BSD 2-Clause "Simplified" License:
#	Redistribution and use in source and binary forms, with or without
#	modification, are permitted provided that the following conditions are met:
#	1. Redistributions of source code must retain the above copyright notice, this
#	   list of conditions and the following disclaimer.
#	2. Redistributions in binary form must reproduce the above copyright notice,
#	   this list of conditions and the following disclaimer in the documentation
#	   and/or other materials provided with the distribution.
#
#	SLCAN IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#	OF SLCAN, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#	GNU General Public License v3.0 or later:
#	SLCAN is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	SLCAN is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with SLCAN.  If not, see <https://www.gnu.org/licenses/>.
#
current_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown OS')
current_OS := $(patsubst CYGWIN%,Cygwin,$(current_OS))
current_OS := $(patsubst MINGW%,MinGW,$(current_OS))
current_OS := $(patsubst MSYS%,MinGW,$(current_OS))

MAJOR = 2
MINOR = 0
PATCH = 0

ifeq ($(PATCH),0)
VERSION = $(MAJOR).$(MINOR)
else
VERSION = $(MAJOR).$(MINOR).$(PATCH)
endif

HOME_DIR = ..
MAIN_DIR = .

SOURCE_DIR = $(HOME_DIR)/Sources
SERIAL_DIR = $(SOURCE_DIR)

OBJECTS = $(OUTDIR)/slcan.o $(OUTDIR)/serial.o \
	$(OUTDIR)/buffer.o $(OUTDIR)/queue.o \
	$(OUTDIR)/timer.o $(OUTDIR)/logger.o


ifeq ($(current_OS),Darwin) # macOS - libSLCAN.dylib

LIBRARY = libSLCAN

TARGET  = $(LIBRARY).$(VERSION).dylib
STATIC  = $(LIBRARY).a

INSTALL_NAME = $(TARGET)
CURRENT_VERSION = $(MAJOR).$(MINOR).$(PATCH)
COMPATIBILITY_VERSION = $(MAJOR).$(MINOR).0

INSTALL = /usr/local/lib

INCLUDE = /usr/local/include

DEFINES = -DOPTION_SLCAN_DYLIB=1 \
	-DOPTION_SERIAL_DEBUG_LEVEL=0 \
	-DOPTION_SLCAN_DEBUG_LEVEL=0

HEADERS = -I$(SOURCE_DIR) \

LIBRARIES = -lpthread

CFLAGS += -O2 -Wall -Wno-parentheses \
	-fno-strict-aliasing \
	$(DEFINES) \
	$(HEADERS)

CXXFLAGS += -g -Wall -Wextra -pthread \
	$(DEFINES) \
	$(HEADERS)

LDFLAGS  += -nostartfiles -dynamiclib -fvisibility=hidden \
	-install_name @rpath/$(INSTALL_NAME) \
	-current_version $(CURRENT_VERSION) \
	-compatibility_version $(COMPATIBILITY_VERSION)

LTFLAGS += -static

ifeq ($(BINARY),UNIVERSAL)
CFLAGS += -arch arm64 -arch x86_64
CXXFLAGS += -arch arm64 -arch x86_64
LDFLAGS += -arch arm64 -arch x86_64
endif

CXX = clang++
CC = clang
LD = clang
LT = libtool
endif

ifeq ($(current_OS),$(filter $(current_OS),Linux Cygwin)) # linux - libslcan.so.1

LIBRARY = libslcan

SONAME  = $(LIBRARY).so.1
TARGET  = $(SONAME).$(VERSION)
STATIC  = $(LIBRARY).a

INSTALL = /usr/local/lib

INCLUDE = /usr/local/include

DEFINES = -DOPTION_SLCAN_SO=1 \
	-DOPTION_SERIAL_DEBUG_LEVEL=0 \
	-DOPTION_SLCAN_DEBUG_LEVEL=0

HEADERS = -I$(SOURCE_DIR)

CFLAGS += -fPIC -O2 -Wall -Wno-parentheses \
	-fno-strict-aliasing \
	$(DEFINES) \
	$(HEADERS)

LIBRARIES = -lpthread

CXXFLAGS += -fPIC -g -Wall -Wextra -pthread \
	$(DEFINES) \
	$(HEADERS)

LDFLAGS  += --shared -Wl,-soname,$(SONAME) -lc

ARFLAGS = r

CXX = g++
CC = gcc
LD = gcc
AR = ar
endif

RM = rm -f
CP = cp -f
LN = ln -s

OUTDIR = .objects
BINDIR = $(HOME_DIR)/Binaries
INCDIR = $(HOME_DIR)/Includes

.PHONY: info outdir bindir incdir


all: info outdir bindir incdir $(STATIC) $(TARGET)

info:
	@echo $(CC)" on "$(current_OS)
	@echo "target: "$(TARGET)
	@echo "install: "$(INSTALL)

outdir:
	@mkdir -p $(OUTDIR)

bindir:
	@mkdir -p $(BINDIR)

incdir:
	@mkdir -p $(INCDIR)
	$(CP) $(SERIAL_DIR)/slcan.h $(INCDIR)
	$(CP) $(SERIAL_DIR)/serial_attr.h $(INCDIR)

clean:
	@-$(RM) $(TARGET) $(STATIC) $(OUTDIR)/*.o $(OUTDIR)/*.d

pristine:
ifeq ($(current_OS),Darwin)
	@-$(RM) *.dylib *.a $(OUTDIR)/*.o $(OUTDIR)/*.d
	@-$(RM) $(BINDIR)/*.dylib $(BINDIR)/*.a
endif
ifeq ($(current_OS),$(filter $(current_OS),Linux Cygwin))
	@-$(RM) *.so *.a $(OUTDIR)/*.o $(OUTDIR)/*.d
	@-$(RM) $(BINDIR)/*.so $(BINDIR)/*.a
endif

install:
	@echo "Copying library file..."
	$(CP) $(TARGET) $(INSTALL)
ifeq ($(current_OS),Darwin)
	@-$(RM) $(INSTALL)/$(LIBRARY).dylib ; $(LN) $(INSTALL)/$(TARGET) $(INSTALL)/$(LIBRARY).dylib
endif
ifeq ($(current_OS),$(filter $(current_OS),Linux Cygwin))
	@-$(RM) $(INSTALL)/$(SONAME) ; ln -s $(INSTALL)/$(TARGET) $(INSTALL)/$(SONAME)
	@-$(RM) $(INSTALL)/$(LIBRARY).so ; ln -s $(INSTALL)/$(SONAME) $(INSTALL)/$(LIBRARY).so
endif



$(OUTDIR)/slcan.o: $(SERIAL_DIR)/slcan.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/serial.o: $(SERIAL_DIR)/serial.c $(SERIAL_DIR)/serial_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/buffer.o: $(SERIAL_DIR)/buffer.c $(SERIAL_DIR)/buffer_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/queue.o: $(SERIAL_DIR)/queue.c $(SERIAL_DIR)/queue_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/timer.o: $(SERIAL_DIR)/timer.c $(SERIAL_DIR)/timer_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/logger.o: $(SERIAL_DIR)/logger.c $(SERIAL_DIR)/logger_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<


$(STATIC): $(OBJECTS)
ifeq ($(current_OS),Darwin)
	$(LT) $(LTFLAGS) -o $@ $(OBJECTS)
	@lipo -archs $@
	$(CP) $(STATIC) $(BINDIR)
	@echo "\033[1mTarget '"$@"' successfully build\033[0m"
endif
ifeq ($(current_OS),$(filter $(current_OS),Linux Cygwin))
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	$(CP) $(STATIC) $(BINDIR)
	@echo "\033[1mTarget '"$@"' successfully build\033[0m"
endif

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBRARIES)
ifeq ($(current_OS),Darwin)
	@lipo -archs $@
endif
	$(CP) $(TARGET) $(BINDIR)
	@echo "\033[1mTarget '"$@"' successfully build\033[0m"
