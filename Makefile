# ID:207192246
# Mail: ShayNamir@gmail.com

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directories
SRC_DIR = .
DEV_CARDS_DIR = ./DevelopCards
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Executable names
TARGET = catan_game
TEST_TARGET = test_catan

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(DEV_CARDS_DIR)/*.cpp)
MAIN_SRCS = $(filter-out $(SRC_DIR)/TestCatan.cpp, $(SRCS))
TEST_SRCS = $(SRC_DIR)/TestCatan.cpp

# Object files
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.cpp, $(MAIN_SRCS)))
MAIN_OBJS += $(patsubst $(DEV_CARDS_DIR)/%.cpp, $(OBJ_DIR)/DevelopCards/%.o, $(filter $(DEV_CARDS_DIR)/%.cpp, $(MAIN_SRCS)))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Include directories
INCLUDES = -I$(SRC_DIR) -I$(DEV_CARDS_DIR)

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR) $(OBJ_DIR)/DevelopCards)

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link object files to create the main executable
$(BIN_DIR)/$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJS) -o $@

# Link object files to create the test executable
$(BIN_DIR)/$(TEST_TARGET): $(MAIN_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJS) $(TEST_OBJS) -o $@

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/DevelopCards/%.o: $(DEV_CARDS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the catan_game executable
catan: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

# Run the test executable
test: $(BIN_DIR)/$(TEST_TARGET)
	./$(BIN_DIR)/$(TEST_TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Phony targets
.PHONY: all clean catan test