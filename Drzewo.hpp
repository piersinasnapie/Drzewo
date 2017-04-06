#ifndef Drzewo_hpp
#define Drzewo_hpp

#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Drzewo
{
private:

	struct Node
	{
		T value;
		Node* parent;
		std::vector<Node*> children; // list of children
        int current_child;

		Node(const T& _value=T(), Node* _parent=nullptr, int _current=0): 
            value(_value), 
            parent(_parent),
            current_child(_current)
            {}
		Node(T && _value, Node* _parent=nullptr): value(std::move(_value)), parent(_parent){}
        // TODO
        ~Node()
        {}
	};

	Node* rootNode;
	size_t numer_of_nodes;

public:

    typedef T value_type;
    typedef T& reference;

	class iterator
    {
    private:

    	Node* ptr;
        friend class Drzewo;

        // PRE-ORDER
        Node* traverse(Node* node)
        {
            if(node == nullptr)
            {
                return node;
            }
            if(node->current_child == node->children.size())
            {
                node->current_child = 0;
                return traverse(node->parent);
            }
            if(node->children.size() != 0)
            {
                int index = node->current_child; 
                node->current_child++;
                return node->children[index];
            }
            return traverse(node);
        }

        iterator(Node* node): ptr(node){}

    public:

        typedef T value_type;

    	iterator(): ptr(nullptr){}
    	iterator(const iterator& iterator): ptr(iterator.ptr){}
        T& operator*(){ return ptr->value; }

        iterator& operator++()
        {
    		ptr = traverse(ptr);
            return *this;
        }

        bool operator!=(const iterator& it){ return this->ptr != it.ptr; }
    };

	Drzewo(): rootNode(nullptr), numer_of_nodes(0){}
    Drzewo(const T& root_value): rootNode(new Node(root_value)), numer_of_nodes(1){}
    // TODO
    Drzewo(const Drzewo & other_tree);
    // TODO
    Drzewo & operator=(const Drzewo & other_tree);
    // TODO
    ~Drzewo()
    {

    }

	iterator insert(const T& value, iterator parent, std::size_t index)
	{
		if(parent.ptr == nullptr && rootNode == nullptr && index == 0)
        {
            rootNode = new Node(value);
            numer_of_nodes++;
            return iterator(rootNode);
        }
        else
		{
			Node* node = new Node(value,parent.ptr);
			std::vector<Node*>* children = &(parent.ptr->children);
			if(index >= parent.ptr->children.size()) // czy ma sens ?
			{
				children->push_back(node);
			}
            else
			{
                // wstawiamy w określone miejsce
				children->insert(children->begin()+index,node);
			}
			numer_of_nodes++;
			return iterator(node);
		}
	}

	// TODO
    void erase(iterator& node)
    {
        auto begin = node.ptr->parent->children.begin();
        auto end = node.ptr->parent->children.end();
        auto it = find(begin,end,node.ptr);
        if(node.ptr == rootNode)
        {

        }
        else
        {
            for(int i=0; i<node.ptr->children.size(); i++)
            {
                Node* temp = traverse(node.ptr);
            }
        }
    }

    iterator getChild(const iterator& parent, std::size_t index)
    {
        return iterator(parent.ptr->children[index]);
    }

    iterator begin(){ return iterator(rootNode); }
    iterator end(){ return iterator(nullptr); }
    iterator root(){ return iterator(rootNode); }
    bool empty(){ return numer_of_nodes == 0; }
    std::size_t size() { return numer_of_nodes; }
    int getNumberOfChildren(const iterator& parent){ return parent.ptr->children.size(); }
};

#endif
