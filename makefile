FLAGS = g++ -Wall -pedantic -std=c++14
TEST_FLAGS = -lcppunit

test: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

run: test
	./test.x

iterator_test: iterator_test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

run_it_test: iterator_test
	./iterator_test.x	
