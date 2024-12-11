# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d


LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -lbox2d
# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Regla para compilar cada archivo .cpp y generar el archivo .exe correspondiente
$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	g++ $< -o $@ $(SFML) -Iinclude

# Crear directorio bin si no existe
$(shell mkdir -p $(BIN_DIR))

# Regla para compilar el juego completo (incluir múltiples archivos .cpp como 08_Tron.cpp y 07_Fisica.cpp)
$(BIN_DIR)/08_Tron.exe: $(SRC_DIR)/08_Tron.cpp $(SRC_DIR)/07_Fisica.cpp $(SRC_DIR)/Player.cpp
	g++ $(SRC_DIR)/08_Tron.cpp $(SRC_DIR)/07_Fisica.cpp $(SRC_DIR)/Player.cpp -o $(BIN_DIR)/08_Tron.exe $(SFML) -Iinclude

# Regla por defecto para compilar todos los archivos .cpp
all: $(BIN_DIR)/08_Tron.exe

# Regla para ejecutar el archivo .exe
run08_Tron: $(BIN_DIR)/08_Tron.exe
	./$(BIN_DIR)/08_Tron.exe

# Regla para limpiar los archivos generados
clean:
	rm -f $(BIN_DIR)/*.exe

.PHONY: all clean
.PHONY: run08_Tron