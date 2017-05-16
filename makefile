FLAGS = g++ -Wall -pedantic -std=c++14
TEST_FLAGS = -lcppunit

# main: main.cpp
# 	$(FLAGS) $^ -o $@.x

test: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

run: test
	./test.x

# run: main
# 	./main.x


