CC = gcc
# Compilation flags
CFLAGS = -std=c99 -pedantic -pedantic-errors -Wall -Wextra -Wformat=2 -Wformat-security -Wnull-dereference -Wstack-protector -Wtrampolines -Walloca -Wvla -Warray-bounds=2 -Wimplicit-fallthrough=3 -Wshift-overflow=2 -Wcast-qual -Wcast-align=strict -Wconversion -Wsign-conversion -Wlogical-op -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnested-externs -Winline -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wshadow -Wwrite-strings -Wfloat-equal -Wpointer-arith -Wbad-function-cast -Wold-style-definition -Isrc -Isrc/include
HARDENING = -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fPIE -fstack-clash-protection -fcf-protection
LDFLAGS = -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,-z,separate-code -pie -flto
OPTFLAGS = -O3 -march=native -flto
ALL_CFLAGS = $(CFLAGS) $(HARDENING) $(OPTFLAGS)
LDLIBS = -lm

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = bin/obj

TARGET = $(BIN_DIR)/conv
SRCS = $(SRC_DIR)/conv.c $(SRC_DIR)/include/set.c
OBJS = $(OBJ_DIR)/conv.o $(OBJ_DIR)/include/set.o

.PHONY: all clean install format lint fix

all: $(TARGET) $(BIN_DIR)/.symlinks

$(BIN_DIR)/.symlinks: $(TARGET)
	ln -sf conv $(BIN_DIR)/c2f
	ln -sf conv $(BIN_DIR)/f2c
	ln -sf conv $(BIN_DIR)/k2l
	ln -sf conv $(BIN_DIR)/l2k
	ln -sf conv $(BIN_DIR)/m2i
	ln -sf conv $(BIN_DIR)/i2m
	ln -sf conv $(BIN_DIR)/m2f
	ln -sf conv $(BIN_DIR)/f2m
	ln -sf conv $(BIN_DIR)/k2m
	ln -sf conv $(BIN_DIR)/m2k
	ln -sf conv $(BIN_DIR)/c2i
	ln -sf conv $(BIN_DIR)/i2c
	ln -sf conv $(BIN_DIR)/m2y
	ln -sf conv $(BIN_DIR)/y2m

format:
	clang-format -style=file:./.clang-format -i $(SRCS)
	mbake format --config ./.bake.toml Makefile

CLANG_TIDY_CHECKS = -checks=-*,bugprone-*,clang-analyzer-*
CLANG_TIDY_FLAGS = -std=c99 -pedantic -Wall -Wextra -Isrc -Isrc/include

lint:
	clang-tidy $(CLANG_TIDY_CHECKS) $(SRCS) -- $(CLANG_TIDY_FLAGS)
	mbake validate --config ./.bake.toml Makefile

fix:
	clang-tidy --fix $(CLANG_TIDY_CHECKS) $(SRCS) -- $(CLANG_TIDY_FLAGS)

$(TARGET): $(OBJS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) -c $< -o $@

$(OBJ_DIR)/include/%.o: $(SRC_DIR)/include/%.c
	mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) -c $< -o $@

test:
	$(CC) -Itests/include tests/test_placeholder.c -o tests/runner
	./tests/runner

clean:
	rm -rf $(BIN_DIR)
