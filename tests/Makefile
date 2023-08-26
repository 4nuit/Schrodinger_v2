TESTHEADERS=$(wildcard *.h)
TESTSOURCES=$(patsubst %.h, %.cpp, $(TESTHEADERS))
TESTOBJ=obj/tests.o
TESTCPP=tests.cpp
TARGET=bin/test

PROJECTOBJ_A_TEST=../obj/algorithms.o ../obj/poly.o ../obj/dataExporter.o ../obj/basis.o
CXX=cxxtestgen
CC=g++
CFLAGS=-Wall -Wextra -std=c++11 -O3
LFLAGS=-larmadillo

###
#  Les tests ont besoin des .obj pour pouvoir se faire, donc on va aller les chercher en les compilant d'abord.
#  On peut ensuite lancer cxxtestgen et compiler notre exécutable de test. Et enfin on le lance.
###
all: compile_project_obj CXX compile_test

## Lancement des tests ##
run_test:
	@echo "Lancement des tests\n-----------------"
	./$(TARGET)

## Compilation de l'exécutable des tests ##
compile_test: $(TESTOBJ) $(PROJECTOBJ_A_TEST)| bin #Créer le dossier bin s'il n'existe pas
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)

$(TESTOBJ): $(TESTCPP) | obj #Créer le dossier obj s'il n'existe pas
	$(CC) $(CFLAGS) $< -c -o $@ $(LFLAGS)

## CXXtest ##
CXX: $(TESTHEADERS)
	$(CXX) --error-printer -o $(TESTCPP) $^

## Compilation des obj du projet ##
compile_project_obj:
	@echo "Démarrage des tests\n-----------------"
	@echo "Préparation des .obj du projet, peut prendre un peu de temps."
	$(MAKE) -C .. compile_source

## Target&Obj clean ##
.PHONY: clean
clean:
	rm -f $(TESTOBJ)
	rm -f $(TARGET)
	rm -f $(TESTSOURCES)
	rm -f tests.cpp

## Création des dossiers obj et bin ##
obj:
	mkdir -p $@
bin:
	mkdir -p $@