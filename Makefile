# Compilation
CC=g++
CFLAGS=-std=c++17 -Wall -Wextra
LIBS=-lGL -lglfw -lGLEW
COMPILE=$(CC) $(CFLAGS) $(LIBS) $^ -o $@
# Directories
SRC_DIR=src
OBJ_DIR=obj
TST_DIR=test
# Files
SRCS=$(wildcard $(SRC_DIR)/**/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TSTS=$(patsubst %.cpp, %, $(wildcard $(TST_DIR)/*/main.cpp))

PHONY := all
all: tests

PHONY += tests
tests: $(TSTS)

# Build test
$(TST_DIR)/%: $(TST_DIR)/%.cpp $(OBJS)
	$(COMPILE)

# Build object
${OBJS}: $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(COMPILE) -c

PHONY += clean
clean:
	rm -r -f $(OBJ_DIR)
	rm -f $(TSTS)

PHONY += test
test: obj/util/name_map.o

.PHONY: $(PHONY)
