//
//  drzewo.cpp
//  Drzewo
//
//  Created by Joanna Janos on 25.03.2017.
//  Copyright © 2017 Joanna Janos. All rights reserved.
//

#include <iostream>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>

#include "../drzewo.hpp"

using namespace std;


//TESTY DRZEWO

class EmptyTest : public CppUnit::TestFixture  {
private:
public:
    //funkcja wywoływana przed KAZDYM testem
    void setUp(){
    }
    //funkcja wywoływana po KAZDYM tescie
    void tearDown(){
    }
    
    void empty_tree_without_root(){
        Drzewo<int> d;
        CPPUNIT_ASSERT_EQUAL(true,d.empty());
    }
    
    void empty_tree_with_root(){
        Drzewo<int> d1(1);
        CPPUNIT_ASSERT_EQUAL(false,d1.empty());
    }
    
    void empty_tree_no_root_insert(){
        Drzewo<int> d;
        d.insert(2, d.end(), 0);
        CPPUNIT_ASSERT_EQUAL(false,d.empty());
    }
    
    void empty_tree_root_insert(){
        Drzewo<int> d1(1);
        d1.insert(2, d1.root(), 0);
        CPPUNIT_ASSERT_EQUAL(false,d1.empty());
    }
    
    void empty_tree_root_erase(){
        Drzewo<int> d1(1);
        d1.erase(d1.root());
        CPPUNIT_ASSERT_EQUAL(true,d1.empty());
    }
    
    void empty_tree_no_root_i_erase(){
        Drzewo<int> d;
        Drzewo<int>::iterator i = d.insert(2, d.end(), 0);
        d.erase(i);
        CPPUNIT_ASSERT_EQUAL(true,d.empty());
    }
    
    void empty_tree_root_i_erase(){
        Drzewo<int> d1(1);
        Drzewo<int>::iterator i = d1.insert(2, d1.root(), 0);
        d1.erase(i);
        CPPUNIT_ASSERT_EQUAL(false,d1.empty());
    }
};


class SizeTest : public CppUnit::TestFixture  {

public:
    void size_tree_without_root(){
        Drzewo<int> d;
        CPPUNIT_ASSERT_EQUAL(true,(d.size()==0));
    }
    void size_with_root(){
        Drzewo<int> d1(1);
        CPPUNIT_ASSERT_EQUAL(true,(d1.size()==1));
    }
    void size_with_root_3insert_2erase(){
        Drzewo<int> d1(1);
        Drzewo<int>::iterator i1=d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i2= d1.insert(3, d1.root(), 1);
        d1.insert(4, d1.root(), 1);
        d1.erase(i2);
        d1.erase(i1);
        CPPUNIT_ASSERT_EQUAL(true,(d1.size()==2));
    }
};



// class RootTest : public CppUnit::TestFixture  {

// public:
    
//     void root_tree_without_root(){
//         Drzewo<int> d;
//         CPPUNIT_ASSERT_EQUAL(true,(d.root()==nullptr));
//     }
    
//     void root_tree_with_root_erase(){
//         Drzewo<int> d1(1);
//         d1.erase(d1.root());
//         CPPUNIT_ASSERT_EQUAL(true,(d1.root()==nullptr));
//     }
    
//     void root_tree_with_root_erase_2insert(){
//         Drzewo<int> d1(1);
//         d1.erase(d1.root());
//         d1.insert(2, d1.end(), 0);
//         d1.insert(3, d1.root(), 0);
//         CPPUNIT_ASSERT_EQUAL(false,(d1.root()==nullptr));
//     }
   
// };


class GetChildTest : public CppUnit::TestFixture  {
public:
    
    // void getChild_tree_with_root(){
    //     Drzewo<int> d1(1);
    //     // CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(), 0))==nullptr);
    // }
    void getChild_tree_with_root_3insert(){
        Drzewo<int> d1(10);
        Drzewo<int>::iterator i1=d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i2=d1.insert(3, d1.root(), 0);
        Drzewo<int>::iterator i3=d1.insert(1, d1.root(), 0);
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(), 2)==i1));
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(), 1)==i2));
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(), 0))==i3);
    }
};

class GetNumberOfChildrenTest : public CppUnit::TestFixture  {
public:
    
    void getNumberOfChildren_tree_with_root(){
        Drzewo<int> d1(1);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(d1.root())==0);
    }
    void getNumberOfChildren_tree_with_root_insert_checkRoot(){
        Drzewo<int> d1(1);
        d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i=d1.insert(3, d1.root(), 1);
        d1.insert(4, d1.root(), 2);
        d1.insert(2, i, 0);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(d1.root())==3);
    }
    void getNumberOfChildren_tree_with_root_insert_checkChild(){
        Drzewo<int> d1(1);
        d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i1=d1.insert(3, d1.root(), 1);
        d1.insert(4, d1.root(), 2);
        d1.insert(2, i1, 0);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(i1)==1);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(d1.root())==3);

    }
    
};

class EraseTest : public CppUnit::TestFixture  {
public:
    void erase_tree_with_root(){
        Drzewo<int> d1(1);
        d1.erase(d1.root());
        CPPUNIT_ASSERT_EQUAL(true,(d1.size()==0));
    }
    void erase_tree_with_root_3insert_2erase(){
        Drzewo<int> d1(1);
        Drzewo<int>::iterator i1=d1.insert(2, d1.root(), 0);
        d1.insert(3, d1.root(), 0);
        Drzewo<int>::iterator i3=d1.insert(1, d1.root(), 0);
        d1.erase(i1);
        d1.erase(i3);
        CPPUNIT_ASSERT_EQUAL(true,(d1.size()==2));
    }
    void erase_with_root_5insert_2erase(){
        Drzewo<int> d1(30);
        d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i1=d1.insert(3, d1.root(), 0);
        d1.insert(5, d1.root(), 0);
        Drzewo<int>::iterator i2=d1.insert(2, i1, 0);
        d1.insert(9, i1, 1);
        d1.erase(i2);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(i1)==1);
        d1.erase(i1);
        CPPUNIT_ASSERT_EQUAL(true,d1.getNumberOfChildren(d1.root())==2);
        
    }
    
    void erase_tree_without_root_insert(){
        Drzewo<int> d1;
        Drzewo<int>::iterator i1=d1.insert(2, d1.end(), 0);
        Drzewo<int>::iterator i2=d1.insert(2, d1.root(), 0);
        Drzewo<int>::iterator i3=d1.insert(2, d1.root(), 1);
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(),0))==i2);
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(),1))==i3);
        
    }
    
};

class InsertTest : public CppUnit::TestFixture  {
public:
    void insert_tree_with_root_2insert(){
        Drzewo<int> d1(1);
        Drzewo<int>::iterator i1=d1.insert(2, d1.root(), 0);
        d1.insert(3, d1.root(), 1);
        CPPUNIT_ASSERT_EQUAL(true,(d1.getChild(d1.root(),0)==i1));
    }
    
    void insert_noroot(){
        Drzewo<int> d;
        d.insert(20, d.end(), 0);
        Drzewo<int>::iterator i1 = d.insert(1, d.root(), 0);
        Drzewo<int>::iterator i2 = d.insert(2, d.root(), 1);
        d.insert(3, i1, 0);
        d.erase(i1);
//        cout<<*(d.getChild(d.root(),0))<<endl;
        CPPUNIT_ASSERT_EQUAL(true,(d.getChild(d.root(),0)==i2));
        
    }
};


//TESTY NODE
// class getNumOfChildrenTest : public CppUnit::TestFixture  {
// public:
//     void getNumOfChildrenT(){
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* leftCh=new Node<int>(8,first);
//         (*first).setLeftChild(leftCh);
//         (*first).increaseNumberOfChildren();
//         Node<int>* Sibling1=new Node<int>(12,first);
//         (*first).increaseNumberOfChildren();
//         Node<int>* Sibling2=new Node<int>(13,first);
//         (*first).increaseNumberOfChildren();
//         Node<int>* Sibling3=new Node<int>(45,first);
//         (*first).increaseNumberOfChildren();
//         (*leftCh).setSibling(Sibling1);
//         (*Sibling1).setSibling(Sibling2);
//         (*Sibling2).setSibling(Sibling3);
//         Node<int>* Sibling4=new Node<int>(12,Sibling2);
//         (*Sibling2).increaseNumberOfChildren();
//         CPPUNIT_ASSERT_EQUAL(true,((*first).getNumOfChildren()==4));
//         CPPUNIT_ASSERT_EQUAL(true,((*leftCh).getNumOfChildren()==0));
//         CPPUNIT_ASSERT_EQUAL(true,((*Sibling2).getNumOfChildren()==1));
//     }
// };


// class getLeftChildTest : public CppUnit::TestFixture  {
// public:
//     void getLeftChildT(){
        
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* Sibling1=new Node<int>(12,nullptr);
//         (*first).setSibling(Sibling1);
//         Node<int>* Sibling2=new Node<int>(13,nullptr);
//         (*Sibling1).setSibling(Sibling1);
//         Node<int>* toFind=new Node<int>(13,Sibling1);
//         (*Sibling1).setLeftChild(toFind);
//         (*Sibling1).increaseNumberOfChildren();
//         CPPUNIT_ASSERT_EQUAL(true,(( first->getSibling() )->getLeftChild()==toFind));
//     }
    
//     void getLeftChildT2(){
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* leftCh=new Node<int>(8,first);
//         (*first).setLeftChild(leftCh);
//         (*first).increaseNumberOfChildren();
//         Node<int>* leftCh2=new Node<int>(12,leftCh);
//         (*leftCh).setLeftChild(leftCh2);
//         (*leftCh).increaseNumberOfChildren();
//         CPPUNIT_ASSERT_EQUAL(true,(( first->getLeftChild() )->getLeftChild()==leftCh2));

//     }
// };

// class getSiblingTest : public CppUnit::TestFixture  {
// public:
//     void getSiblingT(){
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* Sibling1=new Node<int>(12,nullptr);
//         (*first).setSibling(Sibling1);
//         Node<int>* Sibling2=new Node<int>(13,nullptr);
//         (*Sibling1).setSibling(Sibling2);
//         CPPUNIT_ASSERT_EQUAL(true,(( first->getSibling() )->getSibling()==Sibling2));
//     }
    
//     void getSiblingT2(){
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* leftCh=new Node<int>(8,first);
//         (*first).setLeftChild(leftCh);
//         (*first).increaseNumberOfChildren();
//         Node<int>* Sibling1=new Node<int>(12,nullptr);
//         (*leftCh).setSibling(Sibling1);
//         (*first).increaseNumberOfChildren();
//         CPPUNIT_ASSERT_EQUAL(true,(( first->getLeftChild() )->getSibling()==Sibling1));
//     }
// };



// class getParentTest : public CppUnit::TestFixture  {
// public:
//     void getParentT(){
//         Node<int>* first=new Node<int>(3,nullptr);
//         Node<int>* leftCh=new Node<int>(8,first);
//         (*first).setLeftChild(leftCh);
//         (*first).increaseNumberOfChildren();
//         Node<int>* Sibling1=new Node<int>(12,first);
//         (*leftCh).setSibling(Sibling1);
//         (*first).increaseNumberOfChildren();
//         CPPUNIT_ASSERT_EQUAL(true,((((first->getLeftChild())->getSibling())->getParent())==first));
//     }
    
// };



int main(int argc, const char * argv[]) {
//    Drzewo<int> drzewo(10);
//    drzewo.insert(1, drzewo.root(), 0 );
//    Drzewo<int>::iterator i = drzewo.insert(2, drzewo.root(),0);
//    drzewo.insert(10,i,0);
//    drzewo.insert(10,i,1);
//    drzewo.insert(10,i,0);
//    drzewo.erase(i);
//    cout<<drzewo.getNumberOfChildren(drzewo.root())<<endl;
//    cout<<"size: " << drzewo.size()<<endl;
//    
//  
//    
//    Drzewo<string> drzewoS("aa");
//    drzewoS.insert("bbb", drzewoS.root(), 0);
//    cout<<drzewoS.size()<<endl;
    
    
    
    //TESTY
    CppUnit::TextUi::TestRunner runner;
    
    CppUnit::TestSuite *empty_suite= new CppUnit::TestSuite();
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_without_root", &EmptyTest::empty_tree_without_root));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_with_root", &EmptyTest::empty_tree_with_root));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_no_root_insert", &EmptyTest::empty_tree_no_root_insert));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_root_insert", &EmptyTest::empty_tree_root_insert));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_root_erase", &EmptyTest::empty_tree_root_erase));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_no_root_i_erase", &EmptyTest::empty_tree_no_root_i_erase));
    empty_suite->addTest(new CppUnit::TestCaller<EmptyTest> ( "empty_tree_root_i_erase", &EmptyTest::empty_tree_root_i_erase));
    
    
    CppUnit::TestSuite *size_suite= new CppUnit::TestSuite();
    size_suite->addTest(new CppUnit::TestCaller<SizeTest> ( "size_tree_without_root", &SizeTest::size_tree_without_root));
    size_suite->addTest(new CppUnit::TestCaller<SizeTest> ( "size_with_root", &SizeTest::size_with_root));
    size_suite->addTest(new CppUnit::TestCaller<SizeTest> ( "size_with_root_3insert_2erase", &SizeTest::size_with_root_3insert_2erase));

    
    // CppUnit::TestSuite *root_suite= new CppUnit::TestSuite();
    // root_suite->addTest(new CppUnit::TestCaller<RootTest> ( "root_tree_without_root", &RootTest::root_tree_without_root));
    // root_suite->addTest(new CppUnit::TestCaller<RootTest> ( "root_tree_with_root_erase", &RootTest::root_tree_with_root_erase));
    // root_suite->addTest(new CppUnit::TestCaller<RootTest> ( "root_tree_with_root_erase_2insert", &RootTest::root_tree_with_root_erase_2insert));

    
    CppUnit::TestSuite *getChild_suite= new CppUnit::TestSuite();
    // getChild_suite->addTest(new CppUnit::TestCaller<GetChildTest> ( "getChild_tree_with_root", &GetChildTest::getChild_tree_with_root));
    getChild_suite->addTest(new CppUnit::TestCaller<GetChildTest> ( "getChild_tree_with_root_3insert", &GetChildTest::getChild_tree_with_root_3insert));
    
    
    CppUnit::TestSuite *getNumberOfChildren_suite= new CppUnit::TestSuite();
    getNumberOfChildren_suite->addTest(new CppUnit::TestCaller<GetNumberOfChildrenTest> ( "getNumberOfChildren_tree_with_root", &GetNumberOfChildrenTest::getNumberOfChildren_tree_with_root));
    getNumberOfChildren_suite->addTest(new CppUnit::TestCaller<GetNumberOfChildrenTest> ( "getNumberOfChildren_tree_with_root_insert_checkRoot", &GetNumberOfChildrenTest::getNumberOfChildren_tree_with_root_insert_checkRoot));
    getNumberOfChildren_suite->addTest(new CppUnit::TestCaller<GetNumberOfChildrenTest> ( "getNumberOfChildren_tree_with_root_insert_checkChild", &GetNumberOfChildrenTest::getNumberOfChildren_tree_with_root_insert_checkChild));

    
    
     CppUnit::TestSuite *erase_suite= new CppUnit::TestSuite();
    erase_suite->addTest(new CppUnit::TestCaller<EraseTest> ( "erase_tree_with_root", &EraseTest::erase_tree_with_root));
    erase_suite->addTest(new CppUnit::TestCaller<EraseTest> ( "erase_tree_with_root_3insert_2erase", &EraseTest::erase_tree_with_root_3insert_2erase));
    erase_suite->addTest(new CppUnit::TestCaller<EraseTest> ( "erase_with_root_5insert_2erase", &EraseTest::erase_with_root_5insert_2erase));
    erase_suite->addTest(new CppUnit::TestCaller<EraseTest> ( "erase_tree_without_root_insert", &EraseTest::erase_tree_without_root_insert));

    
    CppUnit::TestSuite *insert_suite= new CppUnit::TestSuite();
    insert_suite->addTest(new CppUnit::TestCaller<InsertTest> ( "insert_tree_with_root_2insert", &InsertTest::insert_tree_with_root_2insert));
    insert_suite->addTest(new CppUnit::TestCaller<InsertTest> ( "insert_noroot", &InsertTest::insert_noroot));

    
    
    
    //TESTY NODE
    // CppUnit::TestSuite *getNumOfChildren_suite= new CppUnit::TestSuite();
    // getNumOfChildren_suite->addTest(new CppUnit::TestCaller<getNumOfChildrenTest> ( "getNumOfChildrenT", &getNumOfChildrenTest::getNumOfChildrenT));
    
    // CppUnit::TestSuite *getLeftChild_suite= new CppUnit::TestSuite();
    // getLeftChild_suite->addTest(new CppUnit::TestCaller<getLeftChildTest> ( "getLeftChildT", &getLeftChildTest::getLeftChildT));
    // getLeftChild_suite->addTest(new CppUnit::TestCaller<getLeftChildTest> ( "getLeftChildT2", &getLeftChildTest::getLeftChildT2));
    
    // CppUnit::TestSuite *getSibling_suite= new CppUnit::TestSuite();
    // getSibling_suite->addTest(new CppUnit::TestCaller<getSiblingTest> ( "getSiblingT", &getSiblingTest::getSiblingT));
    // getSibling_suite->addTest(new CppUnit::TestCaller<getSiblingTest> ( "getSiblingT2", &getSiblingTest::getSiblingT2));
    
    // CppUnit::TestSuite *getParent_suite= new CppUnit::TestSuite();
    // getParent_suite->addTest(new CppUnit::TestCaller<getParentTest> ( "getParentT", &getParentTest::getParentT));
    
    
    
    //TESTY DRZEWO
    runner.addTest(empty_suite);
    runner.addTest(size_suite);
    // runner.addTest(root_suite);
    runner.addTest(getChild_suite);
    runner.addTest(getNumberOfChildren_suite);
    runner.addTest(erase_suite);
    runner.addTest(insert_suite);
    //TESTY NODE
    // runner.addTest(getNumOfChildren_suite);
    // runner.addTest(getLeftChild_suite);
    // runner.addTest(getSibling_suite);
    // runner.addTest(getParent_suite);
    
    
   runner.run();
    
    
    
    
        // Drzewo<int> drzewo(10);
        // drzewo.insert(1, drzewo.root(), 0 );
//        Drzewo<int>::iterator i = drzewo.insert(2, drzewo.root(),0);
//    cout<<*(drzewo.getChild(drzewo.root(),0))<<endl;
//        drzewo.insert(10,i,0);
//        drzewo.insert(10,i,1);
//        drzewo.insert(10,i,0);
    // for(Drzewo<int>::iterator it= drzewo.begin();it!=drzewo.end();it++){
    //     cout<< *it<<endl;
    // }
    
    
    
    return 0;
}
