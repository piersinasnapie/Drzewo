#include <iostream>

#include "Drzewo.hpp"

using namespace std;

int main()
{
	Drzewo<int> tree;
	auto root = tree.insert(3,tree.end(),0);

	cout << "Root : " << *tree.root() << endl;

	auto grandpa = tree.insert(4,root,0);

	auto son = tree.insert(2,grandpa,0);
	for(int i=1; i<10; i++)
		son = tree.insert(2,grandpa,i);


	auto grandson = tree.insert(23,son,0);
	auto baby = tree.insert(23,grandson,0);
	auto baby_brother = tree.insert(600,grandson,0);

	tree.erase(root);

	cout << "Tree: " << endl;
	for(const auto& child : tree)
		cout << child << endl;

	// cout << "Deleting : " << *baby << endl;
	// tree.erase(baby);
	// for(const auto& child : tree)
	// 	cout << child << endl;

	// Drzewo<int>::iterator child = tree.getChild(root,0);
	// cout << "Child returned by 'getChild' method: " << *child << endl;

	// cout << "Deleting : " << *grandpa << endl;
	// tree.erase(grandpa);
	// for(const auto& child : tree)
	// 	cout << child << endl;

	cout << "Tree size: " << tree.size() << endl;
	cout << "Number of roots children: " << tree.getNumberOfChildren(root) << endl;

	// tree.erase(root);

	return 0;
}
