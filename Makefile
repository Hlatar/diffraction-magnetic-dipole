CXX      := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra -Iinclude

TARGET   := bin/solver

SRCS     := src/main.cpp src/diffraction.cpp
OBJS     := $(patsubst src/%.cpp,build/%.o,$(SRCS))

# ---- правила сборки ----

all: $(TARGET)

# линковка
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@

# компиляция каждого .cpp -> build/*.o
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- служебное ----

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build bin solution.dat

.PHONY: all clean run