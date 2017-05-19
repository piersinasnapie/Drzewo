FLAGS = g++ -Wall -pedantic -std=c++14 
TEST_FLAGS = -lcppunit

testy_janos: testy_janos.cpp
    $(FLAGS) $^ -o $@.x $(TEST_FLAGS)   

run_testy_janos: testy_janos
    ./testy_janos.x