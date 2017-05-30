#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE iteratorTests
#include <boost/test/unit_test.hpp>
#include "../drzewo.hpp"
#include <list>

BOOST_AUTO_TEST_CASE(rangeBasedLoop) {
    Drzewo<int> tree;
    std::list<int> lst;
    tree.insert(0, tree.end(), 0);
    tree.insert(2, tree.root(), 0);
    auto it = tree.insert(1, tree.root(), 0);
    tree.insert(3, tree.root(), 2);
    tree.insert(4, it, 0);
    tree.insert(5, it, 1);
    for(auto it: tree) {
        lst.push_back(it); }
    lst.sort();
    int i=0;
    for(auto it: lst) {
        BOOST_REQUIRE(it == i++); } }