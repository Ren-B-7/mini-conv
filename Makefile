CC = gcc
# Strict compilation flags
CFLAGS = -std=c90 \
         -pedantic \
         -pedantic-errors \
         -Wall \
         -Wextra \
         -Werror \
         -Wformat=2 \
         -Wformat-security \
         -Wnull-dereference \
         -Wstack-protector \
         -Wtrampolines \
         -Walloca \
         -Wvla \
         -Warray-bounds=2 \
         -Wimplicit-fallthrough=3 \
         -Wtraditional-conversion \
         -Wshift-overflow=2 \
         -Wcast-qual \
         -Wcast-align=strict \
         -Wconversion \
         -Wsign-conversion \
         -Wlogical-op \
         -Wduplicated-cond \
         -Wduplicated-branches \
         -Wrestrict \
         -Wnested-externs \
         -Winline \
         -Wundef \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -Wmissing-declarations \
         -Wredundant-decls \
         -Wshadow \
         -Wwrite-strings \
         -Wfloat-equal \
         -Wpointer-arith \
         -Wbad-function-cast \
         -Wold-style-definition \
         -I src

# Security hardening flags
HARDENING = -D_FORTIFY_SOURCE=2 \
            -fstack-protector-strong \
            -fPIE \
            -fstack-clash-protection \
            -fcf-protection

# Linker hardening flags
LDFLAGS = -Wl,-z,relro \
          -Wl,-z,now \
          -Wl,-z,noexecstack \
          -Wl,-z,separate-code \
          -pie \
          -flto

# Optimization
OPTFLAGS = -O3 -march=native -flto

# Combine all flags
ALL_CFLAGS = $(CFLAGS) $(HARDENING) $(OPTFLAGS)

# Output directories
BIN_DIR = bin
OBJ_DIR = bin/obj
SRC_DIR = src

TARGET = $(BIN_DIR)/conv
TARGET_INSTALL_DIR = $(HOME)/.local/bin/
TARGET_INSTALL = $(TARGET_INSTALL_DIR)/conv

.PHONY: all clean install test valgrind-test format lint fix

all: $(TARGET) $(BIN_DIR)/.symlinks

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(BIN_DIR) $(OBJ_DIR) $(SRC_DIR)/conv.c
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC_DIR)/conv.c

# Create symlinks for all conversion tools using a sentinel file
$(BIN_DIR)/.symlinks: $(TARGET) | $(BIN_DIR)
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
	@touch $(BIN_DIR)/.symlinks

install: $(TARGET) $(BIN_DIR)/.symlinks
	mkdir -p $(TARGET_INSTALL_DIR)
	install -m 755 $(TARGET) $(TARGET_INSTALL_DIR)
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/c2f
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/f2c
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/k2l
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/l2k
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/m2i
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/i2m
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/m2f
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/f2m
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/k2m
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/m2k
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/c2i
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/i2c
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/m2y
	ln -sf $(TARGET_INSTALL) $(TARGET_INSTALL_DIR)/y2m

# Comprehensive tests
test: $(TARGET) $(BIN_DIR)/.symlinks
	@echo "Testing temperature conversions..."
	@# Test C to F (c2f and conv -t -c)
	@for val in "100:212.000" "90:194.000" "80:176.000" "70:158.000" "60:140.000" "50:122.000" \
		"40:104.000" "30:86.000" "20:68.000" "10:50.000" "0:32.000" "-100:-148.000"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./c2f $$input | grep -q -- "$$expected" && echo "✓ c2f $$input passed" || echo "✗ c2f $$input failed"; \
		./conv -t -c $$input | grep -q -- "$$expected" && echo "✓ conv -t -c $$input passed" || echo "✗ conv -t -c $$input failed"; \
	done

	@# Test F to C (f2c and conv -t -f)
	@for val in "212:100.000" "194:90.000" "176:80.000" "158:70.000" "140:60.000" "122:50.000" \
		"104:40.000" "86:30.000" "68:20.000" "50:10.000" "32:0.000" "-148:-100.000"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./f2c $$input | grep -q -- "$$expected" && echo "✓ f2c $$input passed" || echo "✗ f2c $$input failed"; \
		./conv -t -f $$input | grep -q -- "$$expected" && echo "✓ conv -t -f $$input passed" || echo "✗ conv -t -f $$input failed"; \
	done

	@echo "Testing weight conversions..."
	@# Test kg to lb (k2l and conv -w -k)
	@for val in "1:2.205" "10:22.046" "50:110.231" "75:165.347" "100:220.462"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./k2l $$input | grep -q "$$expected" && echo "✓ k2l $$input passed" || echo "✗ k2l $$input failed"; \
		./conv -w -k $$input | grep -q "$$expected" && echo "✓ conv -w -k $$input passed" || echo "✗ conv -w -k $$input failed"; \
	done

	@# Test lb to kg (l2k and conv -w -l)
	@for val in "1:0.454" "10:4.536" "50:22.680" "75:34.019" "100:45.359"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./l2k $$input | grep -q "$$expected" && echo "✓ l2k $$input passed" || echo "✗ l2k $$input failed"; \
		./conv -w -l $$input | grep -q "$$expected" && echo "✓ conv -w -l $$input passed" || echo "✗ conv -w -l $$input failed"; \
	done

	@echo "Testing distance conversions..."
	@# Test m to in (m2i and conv -d -m)
	@for val in "1:39.370" "2:78.740" "5:196.850" "10:393.701"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./m2i $$input | grep -q "$$expected" && echo "✓ m2i $$input passed" || echo "✗ m2i $$input failed"; \
		./conv -d -m $$input | grep -q "$$expected" && echo "✓ conv -d -m $$input passed" || echo "✗ conv -d -m $$input failed"; \
	done

	@# Test in to m (i2m and conv -d -I)
	@for val in "1:0.025" "10:0.254" "50:1.270" "100:2.540"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./i2m $$input | grep -q "$$expected" && echo "✓ i2m $$input passed" || echo "✗ i2m $$input failed"; \
		./conv -d -I $$input | grep -q "$$expected" && echo "✓ conv -d -I $$input passed" || echo "✗ conv -d -I $$input failed"; \
	done

	@# Test m to f (m2f and conv -d -M)
	@for val in "1:3.281" "5:16.404" "10:32.808"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./m2f $$input | grep -q "$$expected" && echo "✓ m2f $$input passed" || echo "✗ m2f $$input failed"; \
		./conv -d -M $$input | grep -q "$$expected" && echo "✓ conv -d -M $$input passed" || echo "✗ conv -d -M $$input failed"; \
	done

	@# Test f to m (f2m and conv -d -F)
	@for val in "1:0.305" "5:1.524" "10:3.048"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./f2m $$input | grep -q "$$expected" && echo "✓ f2m $$input passed" || echo "✗ f2m $$input failed"; \
		./conv -d -F $$input | grep -q "$$expected" && echo "✓ conv -d -F $$input passed" || echo "✗ conv -d -F $$input failed"; \
	done

	@# Test k to m (k2m and conv -d -k)
	@for val in "1:0.621" "10:6.214"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./k2m $$input | grep -q "$$expected" && echo "✓ k2m $$input passed" || echo "✗ k2m $$input failed"; \
		./conv -d -k $$input | grep -q "$$expected" && echo "✓ conv -d -k $$input passed" || echo "✗ conv -d -k $$input failed"; \
	done
	@# Test m to k (m2k and conv -d -mi)
	@for val in "1:1.609" "10:16.093"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./m2k $$input | grep -q "$$expected" && echo "✓ m2k $$input passed" || echo "✗ m2k $$input failed"; \
		./conv -d -mi $$input | grep -q "$$expected" && echo "✓ conv -d -mi $$input passed" || echo "✗ conv -d -mi $$input failed"; \
	done
	@# Test c to i (c2i and conv -d -c)
	@for val in "1:0.394" "10:3.937"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./c2i $$input | grep -q "$$expected" && echo "✓ c2i $$input passed" || echo "✗ c2i $$input failed"; \
		./conv -d -c $$input | grep -q "$$expected" && echo "✓ conv -d -c $$input passed" || echo "✗ conv -d -c $$input failed"; \
	done
	@# Test i to c (i2c and conv -d -i)
	@for val in "1:2.540" "10:25.400"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./i2c $$input | grep -q "$$expected" && echo "✓ i2c $$input passed" || echo "✗ i2c $$input failed"; \
		./conv -d -i $$input | grep -q "$$expected" && echo "✓ conv -d -i $$input passed" || echo "✗ conv -d -i $$input failed"; \
	done

	@# Test m to y (m2y and conv -d -me)
	@for val in "1:1.094" "10:10.936"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./m2y $$input | grep -q "$$expected" && echo "✓ m2y $$input passed" || echo "✗ m2y $$input failed"; \
		./conv -d -me $$input | grep -q "$$expected" && echo "✓ conv -d -me $$input passed" || echo "✗ conv -d -me $$input failed"; \
	done
	@# Test y to m (y2m and conv -d -y)
	@for val in "1:0.914" "10:9.144"; do \
		input=$${val%%:*}; expected=$${val#*:}; \
		./y2m $$input | grep -q "$$expected" && echo "✓ y2m $$input passed" || echo "✗ y2m $$input failed"; \
		./conv -d -y $$input | grep -q "$$expected" && echo "✓ conv -d -y $$input passed" || echo "✗ conv -d -y $$input failed"; \
	done

	@echo "All tests completed."

# Valgrind test
valgrind-test: $(TARGET) $(BIN_DIR)/.symlinks
	valgrind --leak-check=full --error-exitcode=1 ./bin/k2m 1
	valgrind --leak-check=full --error-exitcode=1 ./bin/m2k 1
	valgrind --leak-check=full --error-exitcode=1 ./bin/c2i 1
	valgrind --leak-check=full --error-exitcode=1 ./bin/i2c 1

format:
	clang-format -style=file:./.clang-format -i $(SRC_DIR)/conv.c
	mbake format --config ./.bake.toml Makefile

CLANG_TIDY_FLAGS = -std=c90 -pedantic -Wall -Wextra -Werror

lint:
	clang-tidy $(SRC_DIR)/conv.c -- $(CLANG_TIDY_FLAGS)
	mbake validate --config ./.bake.toml Makefile

# Fix code automatically
fix:
	clang-tidy --fix $(SRC_DIR)/conv.c -- $(CLANG_TIDY_FLAGS)

clean:
	rm -rf $(BIN_DIR)
