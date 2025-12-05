CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -pedantic --std=c++23 -g
BUILD_DIR = build

SOURCES := $(wildcard *.cpp)
TARGETS := $(patsubst %.cpp, $(BUILD_DIR)/%, $(SOURCES))

.PHONY: all clean run

all: $(TARGETS)

$(BUILD_DIR)/%: %.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Building $*..."
	$(CXX) $(CXXFLAGS) -o $@ $<

run:
	@if [ -z "$(filter-out run,$(MAKECMDGOALS))" ]; then \
		echo "Usage: make run <number>"; \
		echo "Example: make run 01"; \
		exit 1; \
	fi
	@$(MAKE) --no-print-directory $(BUILD_DIR)/$(filter-out run,$(MAKECMDGOALS))
	@$(BUILD_DIR)/$(filter-out run,$(MAKECMDGOALS))

%:
	@:

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)
