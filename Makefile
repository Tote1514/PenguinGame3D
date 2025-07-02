# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Bibliotecas necessárias para OpenGL
LIBS = -lglut -lGLU -lGL

# Arquivos fonte e objetos
SRCS = main.cpp Pinguim.cpp Filhote.cpp Peixe.cpp Buraco.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = pinguim3d

# Regra principal: compila tudo
all: $(EXEC)

# Regra para linkar o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

# Regra para compilar cada arquivo .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC)

# Regra para compilar e executar
run: all
	./$(EXEC)
