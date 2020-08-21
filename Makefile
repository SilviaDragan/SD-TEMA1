all: build run
build: 
	gcc main.c dataDefinition.c dataQuery.c dataManipulation.c -o tema1 -Wall -lm
run:
	./tema1
clean: 
	rm tema1