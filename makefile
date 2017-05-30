# podstawowe flagi służące do kompilacji
FLAGS = g++ -Wall -pedantic -std=c++14
# flagi testowe
TEST_FLAGS = -lcppunit

# kompilacja testów dla klasy Drzewo
test: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

mem: mem.cpp
	$(FLAGS) $^ -o $mem.x

# sprawdzenie wycieków pamięci
mem_test:
	c++ -m32 -g -fno-inline -fno-omit-frame-pointer mem.cpp -c -std=c++14
	c++ -m32 -g -fno-inline -fno-omit-frame-pointer mem.o -o mem.x -std=c++14
	DrMemory-MacOS-1.11.0-2/bin/drmemory  -- ./mem.x

# uruchomienie oraz kompilacja zestawu testów dla podstawowych funkcji klasy Drzewo
run_test: test
	./test.x

# kompilacja testów dla klasy iterator
iterator_test: iterator_test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

# uruchomienie oraz kompilacja zestawu testów dla klasy iterator
# dla operatora++
run_iterator_test: iterator_test
	./iterator_test.x	

# czyszczenie katalogu z plików o rozszerzeniach: .x
clean:
	rm -f *.x