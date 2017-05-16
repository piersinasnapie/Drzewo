#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Drzewo.hpp"

using namespace CppUnit;

class  EmptyTest : public TestFixture
{    
public:
    static Test*  suite()
    {
        TestSuite* suite = new TestSuite("'EMPTY' test.");

        suite->addTest(new TestCaller<EmptyTest>("empty_without_root", &EmptyTest::empty_without_root ));
        suite->addTest(new TestCaller<EmptyTest>("empty_with_root", &EmptyTest::empty_with_root ));
        suite->addTest(new TestCaller<EmptyTest>("empty_without_root_insert", &EmptyTest::empty_without_root_insert ));
        // suite->addTest(new TestCaller<EmptyTest>("empty_with_root_erase", &EmptyTest::empty_with_root_erase ));
        // suite->addTest(new TestCaller<EmptyTest>("empty_with_root_insert_erase", &EmptyTest::empty_with_root_insert_erase ));
        // suite->addTest(new TestCaller<EmptyTest>("empty_with_children_erase_root", &EmptyTest::empty_with_children_erase_root ));
        return suite;
    }

    /**
     * Utworzono drzewo z konstruktorem domyślnym
     */
    void empty_without_root()
    {
        Drzewo<int> tree;
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());
    }

    /**
     * Utworzono drzewo z wykorzystaniem konstruktora inicjującego
     */
    void empty_with_root()
    {
        Drzewo<int> tree(4);
        CPPUNIT_ASSERT_EQUAL(false, tree.empty());
    }

    /**
     * Utworzono puste drzewo, a następnie dodano korzeń
     */
    void empty_without_root_insert()
    {
        Drzewo<int> tree;
        tree.insert(4,tree.end(),0);
        CPPUNIT_ASSERT_EQUAL(false, tree.empty());   
    }

    /**
     * Utworzono drzewo z korzeniem, następnie usunięto korzeń
     */
    void empty_with_root_erase()
    {
        Drzewo<int> tree(4);
        auto root = tree.root();
        tree.erase(root);
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());      
    }   

    /**
     * Utworzono drzewo bez korzenia, dodano korzeń, usunięto korzeń
     */
    void empty_with_root_insert_erase()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.erase(root);
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());
    }

    /**
     * Dodano do drzewa dzieci, usunięto korzeń.
     */
    void empty_with_children_erase_root()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(2,root,0);
        auto child = tree.insert(3,root,1);
        tree.insert(1,child,0);
        tree.insert(3,child,1);
        tree.erase(root);
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());   
    }
};

class SizeTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'SIZE' suite");

        suite->addTest(new TestCaller<SizeTest>("one_element_constructor", &SizeTest::one_element_constructor));
        suite->addTest(new TestCaller<SizeTest>("one_element_insert", &SizeTest::one_element_insert));
        suite->addTest(new TestCaller<SizeTest>("zero_elements", &SizeTest::zero_elements));
        suite->addTest(new TestCaller<SizeTest>("more_elements", &SizeTest::more_elements));
        // suite->addTest(new TestCaller<SizeTest>("more_elements_erase_leaf", &SizeTest::more_elements_erase_leaf));
        // suite->addTest(new TestCaller<SizeTest>("more_elements_erase_parent", &SizeTest::more_elements_erase_parent));

        return suite;
    }

    /**
     * Wywołano konstruktor inicjujący
     */
    void one_element_constructor()
    {
        Drzewo<int> tree(4);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 1);
    }

    /**
     * wstawiono element do pustego drzewa
     */
    void one_element_insert()
    {
        Drzewo<int> tree;
        tree.insert(4,tree.end(),0);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 1);
    }

    /**
     * puste drzewo
     */
    void zero_elements()
    {
        Drzewo<int> tree;
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 0);
    }

    /**
     * Dodano więcej elementów
     */
    void more_elements()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(2,root,0);
        auto child = tree.insert(3,root,1);
        tree.insert(1,child,0);
        tree.insert(3,child,1);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 5);
    }

    /**
     * Dodano więcej elementów a potem usunięto liść
     */
    void more_elements_erase_leaf()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(2,root,0);
        auto child = tree.insert(3,root,1);
        tree.insert(1,child,0);
        auto it = tree.insert(3,child,1);
        tree.erase(it);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 4);   
    }

    /**
     * usunięto rodzica, który miał dwoje dzieci
     */
    void more_elements_erase_parent()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(2,root,0);
        auto child = tree.insert(3,root,1);
        tree.insert(1,child,0);
        tree.insert(3,child,1);
        tree.erase(child);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 2);   
    }
};


class GetNumberOfChildrenTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'NUMBER_OF_CHILDREN' suite");

        suite->addTest(new TestCaller<GetNumberOfChildrenTest>("root_no_children", &GetNumberOfChildrenTest::root_no_children));
        suite->addTest(new TestCaller<GetNumberOfChildrenTest>("root_children", &GetNumberOfChildrenTest::root_children));
        suite->addTest(new TestCaller<GetNumberOfChildrenTest>("node_children_insert", &GetNumberOfChildrenTest::node_children_insert));
        // suite->addTest(new TestCaller<GetNumberOfChildrenTest>("node_children_erase", &GetNumberOfChildrenTest::node_children_erase));

        return suite;
    }

    void root_no_children()
    {
        Drzewo<int> tree(1);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(tree.root()) == 0);   
    }

    void root_children()
    {
        Drzewo<int> tree(1);
        tree.insert(2,tree.root(),0);
        tree.insert(3,tree.root(),1);
        tree.insert(4,tree.root(),2);
        tree.insert(5,tree.root(),3);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(tree.root()) == 4);
    }

    void node_children_insert()
    {
        Drzewo<int> tree(1);
        auto it = tree.insert(2,tree.root(),0);
        tree.insert(3,it,1);
        tree.insert(4,it,2);
        tree.insert(5,it,3);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(it) == 3);
        tree.insert(10,it,4);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(it) == 4);
    }

    void node_children_erase()
    {
        Drzewo<int> tree(1);
        auto it = tree.insert(2,tree.root(),0);
        tree.insert(3,it,1);
        tree.insert(4,it,2);
        auto del = tree.insert(5,it,3);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(it) == 3);
        tree.erase(del);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(it) == 2);
    }
};

class GetChildTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'GET_CHILD' suite");

        suite->addTest(new TestCaller<GetChildTest>("root_children", &GetChildTest::root_children));
        suite->addTest(new TestCaller<GetChildTest>("insert_between", &GetChildTest::insert_between));

        return suite;
    }   

    /**
     * sprawdzamy dziecko korzenia
     */
    void root_children()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        auto it = tree.insert(1, root, 0);
        tree.insert(2, root, 1);
        tree.insert(3, root, 2);
        CPPUNIT_ASSERT_EQUAL(true , tree.getChild(root, 0) == it);
    }

    /**
     * wstawiamy pomiędzy dzieci i sprawdzamy czy poprawnie przesunęło
     */
    void insert_between()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        auto it = tree.insert(1, root, 0);
        tree.insert(2, root, 1);
        tree.insert(3, root, 2);
        tree.insert(1, root, 0);
        CPPUNIT_ASSERT_EQUAL(true , tree.getChild(root, 1) == it);   
    }
};


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( EmptyTest::suite() );
    runner.addTest( SizeTest::suite() );
    runner.addTest( GetNumberOfChildrenTest::suite() );
    runner.addTest( GetChildTest::suite() );
    runner.run();
    return 0;
}
