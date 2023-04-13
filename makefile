CFLAGS=-lm -Wall -O0
DEBUG_FLAG=-g
BUILD_DIR=build

# Directories
$(BUILD_DIR)/%:
	mkdir -p $@

# Build object files
%.o: %.c
	$(CC) $< -o $(BUILD_DIR)/$@ $(CFLAGS)

# Ant entry point
ants: $(BUILD_DIR)/ants ants/ant-sim-gen.o
	cp $(BUILD_DIR)/ants/ant-sim-gen.o ant-sim

clean:
	rm -r $(BUILD_DIR)
