# Nombre del compilador
CXX = g++

# Opciones del compilador
CXXFLAGS = -std=c++17 -Wall -O2

# Archivos fuente principales
SOURCES = main.cpp Graph.cpp Algorithm.cpp Flow.cpp State.cpp

# Archivos de cabecera
HEADERS = Graph.h Algorithm.h Flow.h State.h

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = maxflow

# Archivos de test
TEST_STATE = test_State
TEST_ALGORITHM = test_Algorithm
TEST_FLOW = test_Flow
TEST_GRAPH = test_Graph

# Regla principal: compila el ejecutable
all: $(EXECUTABLE)

# Regla para construir el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para construir archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Reglas para compilar y ejecutar los tests
test_algorithm: $(TEST_ALGORITHM).cpp Flow.o Algorithm.o Graph.o State.o
	$(CXX) $(CXXFLAGS) -o $(TEST_ALGORITHM) $^
	./$(TEST_ALGORITHM)

test_state: $(TEST_STATE).cpp State.o Graph.o Flow.o
	$(CXX) $(CXXFLAGS) -o $(TEST_STATE) $^
	./$(TEST_STATE)

test_flow: $(TEST_FLOW).cpp Flow.o
	$(CXX) $(CXXFLAGS) -o $(TEST_FLOW) $^
	./$(TEST_FLOW)

test_graph: $(TEST_GRAPH).cpp Graph.o Flow.o
	$(CXX) $(CXXFLAGS) -o $(TEST_GRAPH) $^
	./$(TEST_GRAPH)

# Regla para ejecutar todos los tests
test: test_algorithm test_state test_flow test_graph

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TEST_STATE) $(TEST_ALGORITHM) $(TEST_FLOW) $(TEST_GRAPH) *.o

# Regla para reconstruir todo
rebuild: clean all