APP_NAME = test
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRC_EXT = c

SRC_DIR = ../console
OBJ_DIR = ../obj
BIN_DIR = ../bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)
APP_SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(BIN_DIR) $(APP_PATH)

-include $(DEPS)

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(APP_PATH): $(OBJ_DIR) $(APP_OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)