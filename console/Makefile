APP_NAME = console
LIB_NAME = libsimplecomputer
LIB2_NAME = libmyterm
CFLAGS = -I../include -Wall -Wextra -Werror
CC = gcc
SRC_EXT = c

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = ../mySimpleComputer/bin/$(LIB_NAME).a ../myTerm/bin/$(LIB2_NAME).a
APP_SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all clean

all: $(BIN_DIR) $(OBJ_DIR) $(LIB_PATH) $(APP_PATH)

-include $(DEPS)

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) -MMD -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
