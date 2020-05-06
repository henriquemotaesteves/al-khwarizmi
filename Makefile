MAIN_BUILD_DIR := build/main
MAIN_SRC_DIR   := src/main
MAIN_SOURCES   := $(wildcard $(MAIN_SRC_DIR)/*.c)
MAIN_OBJECTS   := $(MAIN_SOURCES:$(MAIN_SRC_DIR)/%.c=$(MAIN_BUILD_DIR)/%.o)

TEST_UNIT_BUILD_DIR := build/test/unit
TEST_UNIT_SRC_DIR   := src/test/unit
TEST_UNIT_SOURCES   := $(wildcard $(TEST_UNIT_SRC_DIR)/*.c)
TEST_UNIT_OBJECTS   := $(TEST_UNIT_SOURCES:$(TEST_UNIT_SRC_DIR)/%.c=$(TEST_UNIT_BUILD_DIR)/%.o)
TEST_UNIT_RUNNERS   := $(TEST_UNIT_OBJECTS:.o=.x)

TEST_PERF_BUILD_DIR   := build/test/perf
TEST_PERF_SRC_DIR     := src/test/perf
TEST_PERF_SOURCES     := $(wildcard $(TEST_PERF_SRC_DIR)/*.c)
TEST_PERF_OBJECTS     := $(TEST_PERF_SOURCES:$(TEST_PERF_SRC_DIR)/%.c=$(TEST_PERF_BUILD_DIR)/%.o)
TEST_PERF_ITEMS_COUNT != seq 100
TEST_PERF_RUNNERS     := $(foreach NUMBER_OF_ITEMS,$(TEST_PERF_ITEMS_COUNT),$(TEST_PERF_OBJECTS:.o=.x/$(NUMBER_OF_ITEMS)))
TEST_PERF_PLOTS       := $(wildcard resource/*.gnuplot)

CFLAGS := -Wall -Werror -Wpedantic -std=c99 -I$(MAIN_SRC_DIR)

.PHONY: $(MAIN_SOURCES) $(TEST_UNIT_SOURCES) $(TEST_PERF_SOURCES) $(TEST_UNIT_RUNNERS) $(TEST_PERF_RUNNERS) $(TEST_PERF_PLOTS)

all: clean build test-unit test-perf

clean:
	rm -rf build

build: $(MAIN_OBJECTS) $(TEST_UNIT_OBJECTS) $(TEST_PERF_OBJECTS)

test-unit: clean build $(TEST_UNIT_RUNNERS)

test-perf: clean build $(TEST_PERF_RUNNERS) $(TEST_PERF_PLOTS)

$(MAIN_BUILD_DIR)/%.o: $(MAIN_SRC_DIR)/%.c
	clang-tidy $< -- $(CFLAGS)

	mkdir -p $(dir $@) && gcc $(CFLAGS) -c $< -o $@

$(TEST_UNIT_BUILD_DIR)/%.o: $(TEST_UNIT_SRC_DIR)/%.c
	clang-tidy $< -- $(CFLAGS)

	mkdir -p $(dir $@) && gcc $(CFLAGS) -o $(subst .o,.x,$@) $< $(MAIN_OBJECTS)

$(TEST_PERF_BUILD_DIR)/%.o: $(TEST_PERF_SRC_DIR)/%.c
	clang-tidy $< -- $(CFLAGS)

	mkdir -p $(dir $@) && gcc $(CFLAGS) -I$(TEST_UNIT_SRC_DIR) -o $(subst .o,.x,$@) $< $(MAIN_OBJECTS)

$(TEST_UNIT_RUNNERS):
	exec $@

$(TEST_PERF_RUNNERS):
	valgrind --tool=callgrind --collect-atstart=no --instr-atstart=no --callgrind-out-file=$(@D).$(@F).callgrind $(@D) $(@F)

	grep totals $(@D).$(@F).callgrind | cut -d\: -f2 | tr -d '[:space:]' | xargs -I{} echo "$(@F) {}" >> $(@D).dat

	rm $(@D).$(@F).callgrind

$(TEST_PERF_PLOTS):
	gnuplot $@
