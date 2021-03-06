#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "drzewo.hpp"

using namespace CppUnit;

class EmptyTest : public TestFixture
{    
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'EMPTY' test.");

        suite->addTest(new TestCaller<EmptyTest>("empty_without_root", &EmptyTest::empty_without_root ));
        suite->addTest(new TestCaller<EmptyTest>("empty_with_root", &EmptyTest::empty_with_root ));
        suite->addTest(new TestCaller<EmptyTest>("empty_without_root_insert", &EmptyTest::empty_without_root_insert ));
        suite->addTest(new TestCaller<EmptyTest>("empty_with_root_erase", &EmptyTest::empty_with_root_erase ));
        suite->addTest(new TestCaller<EmptyTest>("empty_with_root_insert_erase", &EmptyTest::empty_with_root_insert_erase ));
        suite->addTest(new TestCaller<EmptyTest>("empty_with_children_erase_root", &EmptyTest::empty_with_children_erase_root ));
        suite->addTest(new TestCaller<EmptyTest>("empty_other_tree", &EmptyTest::empty_other_tree ));

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

    /**
     * Do pustego drzewa przypisujemy inne puste drzewo
     */
    void empty_other_tree()
    {
        Drzewo<double> tree;
        Drzewo<double> other_tree;
        tree = other_tree;
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());
        CPPUNIT_ASSERT_EQUAL(true, other_tree.empty());
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
        suite->addTest(new TestCaller<SizeTest>("more_elements_erase_leaf", &SizeTest::more_elements_erase_leaf));
        suite->addTest(new TestCaller<SizeTest>("more_elements_erase_parent", &SizeTest::more_elements_erase_parent));

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
        suite->addTest(new TestCaller<GetNumberOfChildrenTest>("node_children_erase", &GetNumberOfChildrenTest::node_children_erase));

        return suite;
    }

    /**
     * Utworzono drzewo z korzeniem, bez dzieci. 
     */
    void root_no_children()
    {
        Drzewo<int> tree(1);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(tree.root()) == 0);   
    }

    /**
     * Utworzono drzewo i dodano do korzenia wiele dzieci
     */
    void root_children()
    {
        Drzewo<int> tree(1);
        tree.insert(2,tree.root(),0);
        tree.insert(3,tree.root(),1);
        tree.insert(4,tree.root(),2);
        tree.insert(5,tree.root(),3);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(tree.root()) == 4);
    }

    /**
     * Dodano do korzenia dzieci, a nastepnie jeszcze jedno dziecko.
     */
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

    /**
     * Dodano do korzenia dzieci, a następnie usunięto dziecko. 
     */
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


class InsertTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'INSERT' suite");

        suite->addTest(new TestCaller<InsertTest>("insert_root", &InsertTest::insert_root ));
        suite->addTest(new TestCaller<InsertTest>("insert_root_child", &InsertTest::insert_root_child ));
        suite->addTest(new TestCaller<InsertTest>("insert_front", &InsertTest::insert_front ));

        return suite;
    }

    /**
     * Wstawion korzeń, sprawdzono rozmiar drzewa oraz iterator pokazujący na korzeń.
     */
    void insert_root()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        CPPUNIT_ASSERT_EQUAL(true, root == tree.root());
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 1);
    }

    /**
     * Wstawiono dzieci do korzenia, porównano iteratory i liczby dzieci.
     */
    void insert_root_child()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        auto child = tree.insert(5,root,0);
        CPPUNIT_ASSERT_EQUAL(true, tree.getChild(root,0) == child);
        CPPUNIT_ASSERT_EQUAL(true, tree.size() == 2);
        tree.insert(6,root,1);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(root) == 2);
    }

    /**
     * Wstawiano zawsze jako pierwsze dziecko
     */
    void insert_front()
    {
        Drzewo<int> tree;
        auto root = tree.insert(3,tree.end(),0);
        auto it = tree.insert(1,root,0);
        tree.insert(2,root,0);
        tree.insert(3,root,0);
        CPPUNIT_ASSERT_EQUAL(true, tree.getChild(root,2) == it);
    }
};


class EraseTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'ERASE' suite");

        suite->addTest(new TestCaller<EraseTest>("erase_root", &EraseTest::erase_root ));
        suite->addTest(new TestCaller<EraseTest>("erase_middle_child", &EraseTest::erase_middle_child ));
        suite->addTest(new TestCaller<EraseTest>("erase_child_shift", &EraseTest::erase_child_shift ));
        suite->addTest(new TestCaller<EraseTest>("erase_root_value", &EraseTest::erase_root_value ));
        suite->addTest(new TestCaller<EraseTest>("erase_many_children", &EraseTest::erase_many_children ));
        suite->addTest(new TestCaller<EraseTest>("delete_tree_many_times", &EraseTest::erase_many_children ));

        return suite;
    }

    /** 
     * Usunięto korzeń.
     */
    void erase_root()
    {
        Drzewo<int> tree(4);
        auto root = tree.root();
        tree.erase(root);
        CPPUNIT_ASSERT_EQUAL(true, tree.empty());
    }

    /**
     * Sprawdzana ilość dzieci
     */
    void erase_middle_child()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(1,root,0);
        auto child = tree.insert(2,root,1);
        tree.insert(3,root,2);
        tree.erase(child);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(root) == 2);
    }

    /** 
     * Usunięto środkowe dziecko, sprawdzany porządek wśród dzieci. 
     */
    void erase_child_shift()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        tree.insert(1,root,0);
        auto child = tree.insert(2,root,1);
        auto c = tree.insert(3,root,2);
        tree.erase(child);
        CPPUNIT_ASSERT_EQUAL(true, tree.getChild(root,1) == c);
    }

    /**
     * Sprawdzane poprawne przypisanie korzenia po usunięciu.
     */
    void erase_root_value()
    {
        Drzewo<int> tree(4);
        tree.erase(tree.root());
        CPPUNIT_ASSERT_EQUAL(true, tree.root() == tree.end());
    }

    /**
     * Usunięto wiele dzieci oraz danego rodzica.
     */
    void erase_many_children()
    {
        Drzewo<int> tree(4);
        auto parent = tree.insert(2,tree.root(),0);
        auto uncle = tree.insert(3,tree.root(),1);
        auto son = tree.insert(12,parent,0);
        tree.insert(13,uncle,0);
        tree.insert(22,son,0);
        tree.insert(23,son,1);
        tree.insert(24,son,2);
        int size = tree.size();
        int children_size = tree.getNumberOfChildren(son);
        tree.erase(son);
        CPPUNIT_ASSERT_EQUAL(true, size == tree.size() + children_size + 1);
    }

    /**
     * Bardzo rozbudowane drzewo, usuwamy wiele razy i tworzymy wiele razy
     */
    void delete_tree_many_times()
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

        Drzewo<int> mem_tree = tree;

        // erasing
                
        size_t size = tree.size();

        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(father) == 2);
        tree.erase(son);
        CPPUNIT_ASSERT_EQUAL(true, size == tree.size() + 4 + 1 + 1);    
        CPPUNIT_ASSERT_EQUAL(true, tree.getChild(father, 0) == my_brother);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(father) == 1);
        CPPUNIT_ASSERT_EQUAL(true, *tree.getChild(father, 0) == 121);

        size = tree.size();
        tree.erase(nephew);
        CPPUNIT_ASSERT_EQUAL(true, size == tree.size() + 4 + 1 + 1);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(uncle) == 3);

        size = tree.size();
        tree.erase(daughter);
        CPPUNIT_ASSERT_EQUAL(true, size == tree.size() + 4 + 1);
        CPPUNIT_ASSERT_EQUAL(true, tree.getNumberOfChildren(mom) == 1);
        CPPUNIT_ASSERT_EQUAL(true, *tree.getChild(mom, 0) == 98);
    }
};


class CopyTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'COPY_CONSTRUCTOR' suite");

        suite->addTest( new TestCaller<CopyTest>("copy_constructor", &CopyTest::copy_constructor ));
        suite->addTest( new TestCaller<CopyTest>("operator_equal", &CopyTest::operator_equal ));
        suite->addTest( new TestCaller<CopyTest>("operator_equal_non_empty", &CopyTest::operator_equal_non_empty ));

        return suite;
    }    

    /**
     * Utworzono drzewo za pomocą konstruktora kopiującego 
     */
    void copy_constructor()
    {
        Drzewo<int> other_tree(4);
        other_tree.insert(5,other_tree.root(),0);
        auto parent = other_tree.insert(6,other_tree.root(),1);
        auto uncle = other_tree.insert(7,other_tree.root(),2);
        other_tree.insert(8,other_tree.root(),3);
        other_tree.insert(10,parent,0);
        auto child = other_tree.insert(11,uncle,0);
        other_tree.insert(10,child,0);
        other_tree.insert(13,child,1);
        Drzewo<int> tree(other_tree);
        CPPUNIT_ASSERT_EQUAL(true, other_tree.size() == tree.size());
        CPPUNIT_ASSERT_EQUAL(true, tree.root() != other_tree.root());
    }

    /**
     * Przypisano do pustego drzewa inne drzewo.
     */
    void operator_equal()
    {
        Drzewo<int> other_tree(4);
        other_tree.insert(5,other_tree.root(),0);
        auto parent = other_tree.insert(6,other_tree.root(),1);
        auto uncle = other_tree.insert(7,other_tree.root(),2);
        other_tree.insert(8,other_tree.root(),3);
        other_tree.insert(10,parent,0);
        auto child = other_tree.insert(11,uncle,0);
        other_tree.insert(10,child,0);
        other_tree.insert(13,child,1);
        Drzewo<int> tree = other_tree;

        CPPUNIT_ASSERT_EQUAL(true, other_tree.size() == tree.size());

        size_t other_root_children = other_tree.getNumberOfChildren(other_tree.root());
        size_t tree_root_children = tree.getNumberOfChildren(tree.root());

        CPPUNIT_ASSERT_EQUAL(true, other_root_children == tree_root_children);
        CPPUNIT_ASSERT_EQUAL(true, *other_tree.root() == *tree.root());
        CPPUNIT_ASSERT_EQUAL(true, other_tree.root() != tree.root());

        auto child1 = other_tree.getChild(other_tree.root(), 0);
        auto child2 = tree.getChild(tree.root(), 0);

        CPPUNIT_ASSERT_EQUAL(true, child1 != child2);
    }

    /**
     * Przpisano do niepustego drzewa innego drzewo.
     */
    void operator_equal_non_empty()
    {
        Drzewo<int> other_tree(4);
        other_tree.insert(5,other_tree.root(),0);
        auto parent = other_tree.insert(6,other_tree.root(),1);
        auto uncle = other_tree.insert(7,other_tree.root(),2);
        other_tree.insert(8,other_tree.root(),3);
        other_tree.insert(10,parent,0);
        auto child = other_tree.insert(11,uncle,0);
        other_tree.insert(10,child,0);
        other_tree.insert(13,child,1);

        Drzewo<int> tree(5);
        tree.insert(13,tree.root(),0);
        auto parent2 = tree.insert(11,tree.root(),3);
        tree.insert(5,parent2,0);
        auto son = tree.insert(10,parent2,0);
        tree.insert(1,son,0);
        tree.insert(12,son,1);

        tree = other_tree;
        CPPUNIT_ASSERT_EQUAL(true, other_tree.size() == tree.size());
    }
};


class IteratorTest : public TestFixture
{
public:

    static Test* suite()
    {
        TestSuite* suite = new TestSuite("'ITERATOR' suite");

        suite->addTest( new TestCaller<IteratorTest>("root_test", &IteratorTest::root_test ));
        suite->addTest( new TestCaller<IteratorTest>("root_erase", &IteratorTest::root_erase ));
        suite->addTest( new TestCaller<IteratorTest>("insert_get_child", &IteratorTest::insert_get_child ));
        suite->addTest( new TestCaller<IteratorTest>("operator_asterisk", &IteratorTest::operator_asterisk ));
        suite->addTest( new TestCaller<IteratorTest>("empty_tree", &IteratorTest::empty_tree ));
        suite->addTest( new TestCaller<IteratorTest>("operator_inequal", &IteratorTest::operator_inequal ));
        suite->addTest( new TestCaller<IteratorTest>("operator_equal", &IteratorTest::operator_equal ));

        return suite;
    }

    /**
     * Sprawdzono czy iterator po wstawieniu korzenia pokazuje na korzeń drzewa.
     */
    void root_test()
    {
        Drzewo<int> tree;
        auto root = tree.insert(4,tree.end(),0);
        CPPUNIT_ASSERT_EQUAL(true, root == tree.root());
    }

    /**
     * Usunięto korzeń, iterator powinien pokazuwać na koniec drzewa.
     */
    void root_erase()
    {
        Drzewo<int> tree(4);
        tree.erase(tree.root());
        CPPUNIT_ASSERT_EQUAL(true, tree.root() == tree.end());
    }

    /**
     * Sprawdzono czy iterator zwrócony przez insert i getChild pokazuje na ten sam element.
     */
    void insert_get_child()
    {
        Drzewo<int> tree(4);
        tree.insert(3,tree.root(),0);
        tree.insert(5,tree.root(),1);
        auto it = tree.insert(6,tree.root(),2);
        tree.insert(13,it,0);
        auto child = tree.insert(20,it,0);
        CPPUNIT_ASSERT_EQUAL(true, tree.getChild(it,0) == child);
    }

    /**
     * Sprawdzono poprawność operatora* zwracającego wartość obiektu T przechowywanego w węźle.
     */
    void operator_asterisk()
    {
        Drzewo<char> tree('a');
        CPPUNIT_ASSERT_EQUAL(true, *tree.root() == 'a');
    }

    /**
     * Sprawdzono, iterator na korzeń pokazuje na koniec w przypadku utworzenia pustego drzewa.
     */
    void empty_tree()
    {
        Drzewo<double> tree;
        CPPUNIT_ASSERT_EQUAL(true, tree.root() == tree.end());
    }

    /**
     * Sprawdzenie poprawności działania operatora !=
     */
    void operator_inequal()
    {
        Drzewo<int> tree(4);
        Drzewo<int> other_tree(tree);   
        CPPUNIT_ASSERT_EQUAL(true, tree.root() != other_tree.root());
    }

    /**
     * Sprawdzanie poprawności działania oepratora ==
     */
    void operator_equal()
    {
        Drzewo<double> tree(5.0);
        auto child1 = tree.insert(4,tree.root(),0);
        auto child2 = tree.insert(6,tree.root(),1);
        CPPUNIT_ASSERT_EQUAL(false, child1 == child2);
    }
};


int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest( EmptyTest::suite()                      );
    runner.addTest( SizeTest::suite()                       );
    runner.addTest( GetNumberOfChildrenTest::suite()        );
    runner.addTest( GetChildTest::suite()                   );
    runner.addTest( InsertTest::suite()                     );
    runner.addTest( EraseTest::suite()                      );
    runner.addTest( CopyTest::suite()                       );
    runner.addTest( IteratorTest::suite()                   );

    runner.run();

    return 0;
}
