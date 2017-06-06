#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "drzewo.hpp"

using namespace CppUnit;

class IteratorTest : public TestFixture
{    
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'iterator' test.");

        suite->addTest(new TestCaller<IteratorTest>("empty_tree", &IteratorTest::empty_tree ));
        suite->addTest(new TestCaller<IteratorTest>("only_root", &IteratorTest::only_root ));
        suite->addTest(new TestCaller<IteratorTest>("increment", &IteratorTest::increment ));
        suite->addTest(new TestCaller<IteratorTest>("more_levels", &IteratorTest::more_levels ));
        suite->addTest(new TestCaller<IteratorTest>("show_big_tree", &IteratorTest::show_big_tree ));
        suite->addTest(new TestCaller<IteratorTest>("traverse_empty_tree", &IteratorTest::traverse_empty_tree ));
        suite->addTest(new TestCaller<IteratorTest>("oprator_increment_brother", &IteratorTest::oprator_increment_brother ));
        suite->addTest(new TestCaller<IteratorTest>("operator_increment_child", &IteratorTest::operator_increment_child ));
        suite->addTest(new TestCaller<IteratorTest>("operator_increment_uncle", &IteratorTest::operator_increment_uncle ));
    
        return suite;
    }

    /**
     * Utworzono puste drzewo
     */
    void empty_tree()
    {
        Drzewo<int> tree;
        auto begin = tree.begin();
        auto end = tree.end();
        CPPUNIT_ASSERT_EQUAL(true, begin == end);
    }

    /**
     * Utworzono drzewo z jednym węzłem.
     */
    void only_root()
    {
        Drzewo<int> tree(4);
        auto root = tree.begin();
        ++root;
        CPPUNIT_ASSERT_EQUAL(true, root == tree.end());
    }

    /**
     * "Głupia" inkrementacja
     */
    void increment()
    {
        Drzewo<int> tree;
        auto it = tree.end();
        ++it;
        ++it;
        CPPUNIT_ASSERT_EQUAL(true, it == tree.end());
    }

    /**
     * Utworzono drzewo z dodatkowym poziomem
     */
    void more_levels()
    {
        Drzewo<int> tree;
        auto root = tree.insert(2,tree.end(),0);
        auto child = tree.insert(4,root,0);
        ++child;
        CPPUNIT_ASSERT_EQUAL(true, child == tree.end());
    }

    /** 
     * Utworzono rozbudowane, wielopoziomowe drzewo. Następnie utworzono puste drzewo,
     * będące kopią pierwszego drzewa.
     * W pętli dokonano porównania elementów, poprawności kopiowania oraz zachowania
     * hierarchii drzewa.
     */
    void show_big_tree()
    {
        Drzewo<int> tree(4);
        auto grand = tree.insert(13, tree.root(), 0);
        auto grand_brother = tree.insert(17, tree.root(), 1);
        auto grand_sister = tree.insert(11, tree.root(), 0);

        // grand_sister
        tree.insert(50,grand_sister,0);
        auto mom = tree.insert(72,grand_sister,1);
        tree.insert(81,grand_sister,2);
        auto daughter = tree.insert(15,mom,0);
        tree.insert(111,daughter,0);
        tree.insert(112,daughter,1);
        auto child = tree.insert(113,daughter,2);
        tree.insert(901,child,0);
        tree.insert(98,mom,1);

        // grand
        auto father = tree.insert(70,grand,0);
        auto son = tree.insert(119,father,0);
        auto my_brother = tree.insert(121,father,1);
        for(int i=0; i<3; i++)
        {
            tree.insert(23+i,my_brother,i);
        }
        auto grand_son = tree.insert(287,son,0);
        for(int i=0; i<5; i++)
        {
            tree.insert(100+i,grand_son,i);
        }

        // grand_brother
        auto uncle = tree.insert(701,grand_brother,0);
        Drzewo<int>::iterator nephew = tree.insert(201,uncle,0);
        for(int i=1; i<8; i++)
        {
            nephew = tree.insert(201-2*i,uncle,i); 
        }
        auto c = tree.insert(5,nephew,0);
        tree.insert(4,c,0);
        tree.insert(3,c,0);
        tree.insert(2,c,0);
        tree.insert(1,c,0);

        Drzewo<int> other_tree;
        other_tree = tree;

        auto tree_it = tree.begin();
        auto other_tree_it = other_tree.begin(); 

        CPPUNIT_ASSERT_EQUAL(true, tree.size() == other_tree.size());

        while( tree_it != tree.end() && other_tree_it != other_tree.end() )
        {
            CPPUNIT_ASSERT_EQUAL(true, *tree_it == *other_tree_it);
            CPPUNIT_ASSERT_EQUAL(true, tree_it != other_tree_it);
            CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(tree_it) == other_tree.getNumberOfChildren(other_tree_it));
            if(tree.getNumberOfChildren(tree_it) && other_tree.getNumberOfChildren(other_tree_it))
            {   
                auto v1 = *tree.getChild(tree_it,0);
                auto v2 = *tree.getChild(other_tree_it,0);
                CPPUNIT_ASSERT_EQUAL(true, v1 == v2);
            }

            tree_it++;
            ++other_tree_it;
        }
    }

    /**
     * Utworzono puste drzewo, następnie wykonano dla niego pętlę
     * for-each wypisującą na ekran zawartość drzewa.
     */
    void traverse_empty_tree()
    {
        Drzewo<char> tree;
        for(const auto& it : tree)
        {
            std::cout << it << std::endl;
        }
    }

    /**
     * Sprawdzenie popraności operatora ++ dla węzłów będacych bracmi.
     */
    void oprator_increment_brother()
    {
        Drzewo<int> tree(5);
        tree.insert(1,tree.root(),0);
        auto it = tree.insert(2,tree.root(),1);
        auto brother = tree.insert(3,tree.root(),2);
        ++it;
        CPPUNIT_ASSERT_EQUAL(true, it == brother);
    }

    /**
     * Sprzawdzenie poprawności operator ++ dla węzłów będących w relacji
     * rodzic-dziecko.
     */
    void operator_increment_child()
    {   
        Drzewo<int> tree(5);
        tree.insert(1,tree.root(),0);
        auto it = tree.insert(2,tree.root(),1);
        tree.insert(3,tree.root(),2);
        auto child = tree.insert(12,it,0);
        ++it;
        CPPUNIT_ASSERT_EQUAL(true, it == child);
    }

    /**
     * Sprzawdzenie poprawności operator ++ dla węzłów będących w relacji
     * dziecko-wujek.
     */
    void operator_increment_uncle()
    {   
        Drzewo<int> tree(5);
        tree.insert(1,tree.root(),0);
        auto it = tree.insert(2,tree.root(),1);
        auto uncle = tree.insert(3,tree.root(),2);
        auto child = tree.insert(12,it,0);
        ++child;
        CPPUNIT_ASSERT_EQUAL(true, uncle == child);
    }
};


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( IteratorTest::suite()                      );

    runner.run();

    return 0;   
}