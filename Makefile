CC=g++
CFLAGS=-Wall -Wextra -O3 -std=c++11 
LFLAGS=-larmadillo
TARGET=bin/main
HEADERS=$(wildcard headers/*.h)
HEADERS_ASTYLE=$(wildcard headers/*.h.orig)
SOURCES=$(wildcard src/*.cpp)
SOURCES_ASTYLE=$(wildcard src/*.cpp.orig)
TESTS=$(wildcard tests/*.h)
TESTS_ASTYLE=$(wildcard tests/*.h.orig)
OBJ=$(patsubst src/%.cpp, obj/%.o, $(SOURCES))

all: compile_main

## Edition de liens et compilation exécutable ##

compile_main: $(OBJ) | bin #Créer le dossier bin s'il n'existe pas
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)

obj/%.o: src/%.cpp $(HEADERS) | obj #Créer le dossier obj s'il n'existe pas
	$(CC) $(CFLAGS) $< -c -o $@ $(LFLAGS)

## Création des dossiers obj et bin ##
obj:
	mkdir -p $@
bin:
	mkdir -p $@

## Target&Obj clean ##
.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(TARGET)
	rm -f $(SOURCES_ASTYLE) $(HEADERS_ASTYLE) $(TESTS_ASTYLE)

## Compile seulement les fichiers sources ##
compile_source: $(OBJ)

## Astyle ##
.PHONY: format
format: $(SOURCES) $(HEADERS) $(TESTS)
	./astyle --style=allman $^

## Documentation ##
.PHONY: docs
docs:
	doxygen Doxygen

## Tests ##
.PHONY: tests
tests:
	$(MAKE) -C tests/ all
	
.PHONY: runtests
runtests:
	$(MAKE) -C tests/ all run_test