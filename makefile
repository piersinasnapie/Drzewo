FLAGS = g++ -Wall -pedantic -std=c++14
TEST_FLAGS = -lcppunit

test: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

run: test
	./test.x
