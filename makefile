TARGET    = vpr-omega-zero

CC        = g++
CFLAGS    = -std=c++2a -O2 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion

LD        = g++
LDFLAGS   = 

BIN       = Bin
OBJ       = Build
BUILD     = Build
SOURCE    = Sources

SOURCES   = $(wildcard $(SOURCE)/*.cpp)
OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(OBJ)/%.obj,$(SOURCES))

INCLUDE   = Includes
INCLUDES  = $(addprefix -I,$(INCLUDE))

ifeq ($(PREFIX),)
PREFIX    = /usr/local
endif

all: release debug tests

debug:    CFLAGS  += -g
debug:    TARGET  := $(TARGET)_d
release:  CFLAGS  += -DNDEBUG -O3 -fno-ident -ffast-math -fvisibility=hidden
release:  LDFLAGS += -s

debug: $(TARGET)
release: $(TARGET)

$(TARGET): $(BIN) $(BUILD) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(BIN)/$(TARGET)

$(BIN):
	mkdir -p $@

$(BUILD):
	mkdir -p $@

.PHONY: $(OBJECTS)
$(OBJECTS): $(OBJ)/%.obj : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: tests
tests:
	make -C Tests/ELF all
	make -C Tests/PE all

.PHONY: install
install: release
	install -d $(PREFIX)/bin
	install -m 555 $(BIN)/$(TARGET) $(PREFIX)/bin

.PHONY: clean
clean:
	rm -fr $(BIN)/*
	rm -fr $(BUILD)/*
	make -C Tests/ELF clean
	make -C Tests/PE clean

.PHONY: extra-clean
extra-clean:
	rm -fr $(BIN)
	rm -fr $(BUILD)
	make -C Tests/ELF clean
	make -C Tests/PE clean
