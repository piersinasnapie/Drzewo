FLAGS = g++ -Wall -pedantic -std=c++14

main: main.cpp
	$(FLAGS) $^ -o $@.x

run: main
	./main.x
