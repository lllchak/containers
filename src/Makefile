.PHONY: clean

CC=g++
FLAGS=-Wall -Wextra -Werror 	
BUILD=build/
SOURCEDIR=avl_tree
HEADFILES=$(wildcard $(SOURCEDIR)/*.hpp)
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)

main: clean $(SOURCEDIR)/main.o
	@mkdir $(BUILD)
	$(CC) $(FLAGS) -o $(BUILD)program $(SOURCEDIR)/main.o 

main.o: $(SOURCEDIR)/avl_node.hpp
	$(CC) $(FLAGS) -c $(SOURCES)$


clean:
	rm -Rf $(BUILD)
