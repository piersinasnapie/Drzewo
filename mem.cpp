#include <iostream>

#include "drzewo.hpp"

using namespace std;

void deletePointer(int * ptr){
    delete ptr;
}

int main(int argc, char const *argv[])
{
    // Drzewo<int> tree(4);
    // auto grand = tree.insert(13, tree.root(), 0);
    // auto grand_brother = tree.insert(17, tree.root(), 1);
    // auto grand_sister = tree.insert(11, tree.root(), 0);

    // // grand_sister
    // tree.insert(50,grand_sister,0);
    // auto mom = tree.insert(72,grand_sister,1);
    // tree.insert(81,grand_sister,2);
    // auto daughter = tree.insert(15,mom,0);
    // tree.insert(111,daughter,0);
    // tree.insert(112,daughter,1);
    // auto child = tree.insert(113,daughter,2);
    // tree.insert(901,child,0);
    // tree.insert(98,mom,1);

    // // grand
    // auto father = tree.insert(70,grand,0);
    // auto son = tree.insert(119,father,0);
    // auto my_brother = tree.insert(121,father,1);
    // for(int i=0; i<3; i++)
    // {
    //     tree.insert(23+i,my_brother,i);
    // }
    // auto grand_son = tree.insert(287,son,0);
    // for(int i=0; i<5; i++)
    // {
    //     tree.insert(100+i,grand_son,i);
    // }

    // // grand_brother
    // auto uncle = tree.insert(701,grand_brother,0);
    // Drzewo<int>::iterator nephew = tree.insert(201,uncle,0);
    // for(int i=1; i<8; i++)
    // {
    //     nephew = tree.insert(201-2*i,uncle,i); 
    // }
    // auto c = tree.insert(5,nephew,0);
    // tree.insert(4,c,0);
    // tree.insert(3,c,0);
    // tree.insert(2,c,0);
    // tree.insert(1,c,0);

    return 0;
}