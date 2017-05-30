#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE drzewo
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/bind.hpp>
#include "../drzewo.hpp"

BOOST_AUTO_TEST_CASE( x1 )
{
  Drzewo<int> d;
  BOOST_CHECK_EQUAL(d.empty(),true);
  BOOST_CHECK_EQUAL(d.size(),0);
}
BOOST_AUTO_TEST_CASE( x2 )
{
  Drzewo<int> d(1);
  BOOST_CHECK_EQUAL(d.empty(),false);
  BOOST_CHECK_EQUAL(d.size(),1);
}
BOOST_AUTO_TEST_CASE( x3 )
{
  Drzewo<int> d1;
  Drzewo<int> d2(d1);
  BOOST_CHECK_EQUAL(d2.empty(),true);
  BOOST_CHECK_EQUAL(d2.size(),0);
}
BOOST_AUTO_TEST_CASE( x4 )
{
  Drzewo<int> d1(1);
  Drzewo<int> d2(d1);
  BOOST_CHECK_EQUAL(d2.empty(),false);
  BOOST_CHECK_EQUAL(d2.size(),1);
}

BOOST_AUTO_TEST_CASE( x5 )
{
  Drzewo<char> d;
  char p[9] = {'F','B','A','D','C','E','G','I','H'};
  char r[9];
  d.insert('F',d.end(),0);
  Drzewo<char>::iterator it = d.root();
  d.insert('B',it,0);
  d.insert('G',it,1);
  it = d.getChild(it,0);
  d.insert('A',it,0);
  d.insert('D',it,1);
  it = d.getChild(it,1);
  d.insert('C',it,0);
  d.insert('E',it,1);
  it = d.getChild(d.root(),1);
  d.insert('I',it,0);
  //it.goto_Parent();
  d.insert('H',it,0);
  it = d.begin();
  for(int i = 0; i < 9; ++i)
    {r[i] = *it; ++it;}

    // std::cout<<d.toString();
  BOOST_CHECK_EQUAL(d.size(),9);
  BOOST_CHECK_EQUAL_COLLECTIONS(r,r+9,p,p+9);
}

BOOST_AUTO_TEST_CASE( x6 )
{
    Drzewo<char> d;
    d.insert('F',d.root(),0);
    Drzewo<char>::iterator it = d.root();
    d.insert('B',it,0);
    d.insert('G',it,1);
    Drzewo<char>::iterator prev_it = it;
    BOOST_CHECK((prev_it == it++));
}