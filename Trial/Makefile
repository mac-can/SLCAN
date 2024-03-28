#
#	Trial Program
#	Lawicel SLCAN Protocol
#	Bart Simpson didn't do it
#
current_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown OS')
current_OS := $(patsubst CYGWIN%,Cygwin,$(current_OS))
current_OS := $(patsubst MINGW%,MinGW,$(current_OS))
current_OS := $(patsubst MSYS%,MinGW,$(current_OS))


ifeq ($(current_OS),$(filter $(current_OS),Linux Darwin))
TARGET  = slcan_test
else
TARGET  = slcan_test.exe
endif

INSTALL = ~/bin

HOME_DIR = ..
MAIN_DIR = ./Sources

SOURCE_DIR = $(HOME_DIR)/Sources
SERIAL_DIR = $(SOURCE_DIR)

OBJECTS = $(OUTDIR)/slcan.o $(OUTDIR)/serial.o \
	$(OUTDIR)/buffer.o $(OUTDIR)/queue.o $(OUTDIR)/logger.o \
	$(OUTDIR)/main.o

DEFINES = -DOPTION_SERIAL_DEBUG_LEVEL=1 \
	-DOPTION_SLCAN_DEBUG_LEVEL=1

HEADERS = -I$(SOURCE_DIR) \
	-I$(MAIN_DIR)

LIBRARIES = -lpthread

CFLAGS += -O2 -Wall -Wno-parentheses \
	-fno-strict-aliasing \
	$(DEFINES) \
	$(HEADERS)

CXXFLAGS += -g -Wall -Wextra -pthread \
	$(DEFINES) \
	$(HEADERS)

LDFLAGS  += 

ifeq ($(current_OS),Darwin)  # macOS - libSLCAN.dylib
ifeq ($(BINARY),UNIVERSAL)
CFLAGS += -arch arm64 -arch x86_64
CXXFLAGS += -arch arm64 -arch x86_64
LDFLAGS += -arch arm64 -arch x86_64
endif

CHECKER  = warning,information
IGNORE   = -i *_w.c
ifeq ($(HUNTER),BUGS)
CHECKER += --bug-hunting
endif
endif
ifeq ($(current_OS),Darwin)  # macOS - libSLCAN.dylib
CXX = clang++
CC = clang
LD = clang++
else  # Linux, Cygwin - libSLCAN.so
CXX = g++
CC = gcc
LD = g++
endif
RM = rm -f
CP = cp -f

OUTDIR = .objects


.PHONY: info outdir


all: info outdir $(TARGET)

info:
	@echo $(CXX)" on "$(current_OS)
	@echo "target: "$(TARGET)
	@echo "install: "$(INSTALL)

outdir:
	@mkdir -p $(OUTDIR)

check:
ifeq ($(current_OS),Darwin)  # macOS - libSLCAN.dylib
	cppcheck --enable=$(CHECKER) --suppressions-list=$(HOME_DIR)/suppress.txt \
	-D__APPLE__ $(DEFINES) $(HEADERS) $(IGNORE) $(SOURCE_DIR)
else
	echo "Please use Cppcheck GUI"
endif

clean:
	$(RM) $(TARGET) $(OUTDIR)/*.o $(OUTDIR)/*.d

pristine:
	$(RM) $(TARGET) $(OUTDIR)/*.o $(OUTDIR)/*.d

install:
	$(CP) $(TARGET) $(INSTALL)

test: info outdir $(TARGET)
	./$(TARGET) INFO EXIT

$(OUTDIR)/main.o: $(MAIN_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/slcan.o: $(SERIAL_DIR)/slcan.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/serial.o: $(SERIAL_DIR)/serial.c $(SERIAL_DIR)/serial_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/buffer.o: $(SERIAL_DIR)/buffer.c $(SERIAL_DIR)/buffer_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/queue.o: $(SERIAL_DIR)/queue.c $(SERIAL_DIR)/queue_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<

$(OUTDIR)/logger.o: $(SERIAL_DIR)/logger.c $(SERIAL_DIR)/logger_p.c
	$(CC) $(CFLAGS) -MMD -MF $*.d -o $@ -c $<


$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBRARIES)
	@echo "\033[1mTarget '"$@"' successfully build\033[0m"
