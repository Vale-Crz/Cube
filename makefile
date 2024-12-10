# Directorios
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj
INCLUDE_DIR := include

# Archivos fuente
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET := $(BIN_DIR)/Main.exe

# Compilador y banderas
CXX := g++
CXXFLAGS := -I$(INCLUDE_DIR) -std=c++17 -Wall -Wextra -g
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Regla principal
all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML)

# Regla para compilar cada archivo fuente en objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Regla para ejecutar el programa
runMain: $(TARGET)
	./$(TARGET)

# Limpieza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean runMain
