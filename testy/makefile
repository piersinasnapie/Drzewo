FLAGS = g++ -Wall -pedantic -std=c++14 
CPPUNIT_FLAGS = -lcppunit
BOOST_FLAGS = -lboost_unit_test_framework-mt

testy_janos: testy_janos.cpp
	$(FLAGS) $^ -o $@.x $(CPPUNIT_FLAGS)  

testy_tracz: testy_tracz.cpp
	$(FLAGS) $^ -o $@.x $(BOOST_FLAGS)	 

testy_tracz_iterator: testy_tracz_iterator.cpp
	$(FLAGS) $^ -o $@.x $(BOOST_FLAGS)	 

testy_dawidowicz: testy_dawidowicz.cpp
	$(FLAGS) $^ -o $@.x $(BOOST_FLAGS)

run_testy_janos: testy_janos
	./testy_janos.x

run_testy_tracz: testy_tracz
	./testy_tracz.x

run_testy_tracz_iterator: testy_tracz_iterator
	./testy_tracz_iterator.x

run_testy_dawidowicz: testy_dawidowicz
	./testy_dawidowicz.x
