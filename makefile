# Nombre del compilador
CXX = g++

# Opciones del compilador
CXXFLAGS = -std=c++17 -Wall -O2

# Archivos fuente
SOURCES = main.cpp Graph.cpp Algorithm.cpp Flow.cpp

# Archivos de cabecera
HEADERS = Graph.h Algorithm.h Flow.h 

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = maxflow

# Regla principal: compila el ejecutable
all: $(EXECUTABLE)

# Regla para construir el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para construir archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Regla para reconstruir todo
rebuild: clean all
