# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

# Dependencias para SFML
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.exe, $(CPP_FILES))

# Regla genérica para compilar cualquier archivo .cpp a .exe
$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	g++ $< -o $@ $(SFML) -Iinclude

# Regla específica para 08_Tron.exe con dependencias adicionales
$(BIN_DIR)/08_Tron.exe: $(SRC_DIR)/08_Tron.cpp $(SRC_DIR)/07_Fisica.cpp
	g++ $^ -o $@ $(SFML) -Iinclude

# Objetivo por defecto: compilar todo
all: $(BIN_DIR)/08_Tron.exe $(BIN_DIR)/Ball.exe

# Reglas para ejecutar los binarios
run08_Tron: $(BIN_DIR)/08_Tron.exe
	./$(BIN_DIR)/08_Tron.exe

runBall: $(BIN_DIR)/Main.exe
	./$(BIN_DIR)/Main.exe

# Regla para limpiar los binarios generados
clean:
	rm -f $(BIN_DIR)/*.exe

.PHONY: all clean run08_Tron runBall
