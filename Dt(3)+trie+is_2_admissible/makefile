INCLUDE = ./OGDF/include
LIB = ./OGDF
FILES = tree.o opBasic.o graph.o generator.o

all: $(FILES)
	g++ -std=c++17 -L $(LIB) -o generator generator.o tree.o graph.o opBasic.o -lOGDF -lCOIN

tree.o: lib/tree.cpp lib/tree.hpp
	g++ -std=c++17 -I $(INCLUDE) -c lib/tree.cpp -O3 -march=native -mtune=native

opBasic.o: lib/graph.cpp lib/graph.hpp lib/tree.cpp lib/tree.hpp lib/opBasic.cpp lib/opBasic.hpp
	g++ -std=c++17 -I $(INCLUDE) -c lib/opBasic.cpp -O3 -march=native -mtune=native

graph.o: lib/tree.cpp lib/tree.hpp lib/graph.cpp lib/graph.hpp
	g++ -std=c++17 -I $(INCLUDE) -c lib/graph.cpp -O3 -march=native -mtune=native

generator.o: lib/graph.cpp lib/graph.hpp lib/tree.cpp lib/tree.hpp lib/opBasic.cpp lib/opBasic.hpp generator.cpp
	g++ -std=c++17 -I $(INCLUDE) -c generator.cpp -O3 -march=native -mtune=native

clean:
	rm -rf *.o
	rm generator
