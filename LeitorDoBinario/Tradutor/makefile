INCLUDE = lib
FILES = tradutor.o

all: $(FILES)
	g++ -std=c++17 -o tradutor tradutor.o
	
tradutor.o: tradutor.cpp lib/constants.hpp
	g++ -std=c++17 -I $(INCLUDE) -c tradutor.cpp -O3

clean:
	rm -rf *.o
	rm tradutor
