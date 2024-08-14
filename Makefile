CC = clang
CFLAGS = -Wall -Wextra -Iinclude `pkg-config --cflags glib-2.0` -fPIC
LDFLAGS = `pkg-config --libs glib-2.0`

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

# Use find to get all .c files in src directory and its subdirectories
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# Create object files list with corresponding directory structure in obj
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = $(LIB_DIR)/libtokenizer.so

all: $(TARGET)

$(TARGET): $(OBJS) | $(LIB_DIR)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: all clean
