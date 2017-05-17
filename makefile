FLAGS = g++ -Wall -pedantic -std=c++14 
MEM_FLAGS = -g -fno-inline -fno-omit-frame-pointer
TEST_FLAGS = -lcppunit

# main: main.cpp
# 	$(FLAGS) $^ -o $@.x

test: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS)

memtest: test.cpp
	$(FLAGS) $^ -o $@.x $(TEST_FLAGS) $(MEM_FLAGS)

run: test
	./test.x

# run: main
# 	./main.x


