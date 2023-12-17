# Variáveis
CC = g++
SRC = Proj.cpp
OBJ = $(SRC:.cpp=.o)
EXE = Proj
CFLAGS = -g \
	-fsanitize=address \
	-fno-omit-frame-pointer \
	-fsanitize=undefined \
	-std=c++11 -O3 -Wall -Wextra -pedantic

# Regras
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.d
	rm -f *.out
	rm -f $(OBJ) $(EXE)

run: $(EXE)
	./$(EXE)

memcheck: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE)

# Geração automática de dependências
DEP = $(OBJ:.o=.d)
-include $(DEP)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: all clean run memcheck


