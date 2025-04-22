# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./httplib -Wall -Wextra

# Source and output
SRCS = wstory.cpp receivermain.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = wstory

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
