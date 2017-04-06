#include <iostream>

#include "Drzewo.hpp"

using namespace std;

int main()
{
	Drzewo<int> tree;
	auto root = tree.insert(3,tree.end(),0);
	auto node_1 = tree.insert(4,root,0);
	auto node_2 = tree.insert(2,node_1,0);
	for(int i=1; i<10; i++)
		node_2 = tree.insert(2,node_1,i);


	auto node_3 = tree.insert(23,node_2,0);
	auto node_4 = tree.insert(23,node_3,0);
	auto node_4_1 = tree.insert(600,node_3,0);

	Drzewo<int>::iterator child = tree.getChild(root,0);
	cout << "Child returned by 'getChild' method: " << *child << endl;

	return 0;
}
