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

    void delete_node(Node* node)
    {
        if(node->children.size() == 0)
        {
            Node* temp = node;
            node = node->parent;
            delete temp;
        }
        else
        {
            int index = node->current_child;
            node->current_child++;
            delete_node(node->children[index]);
        }
        numer_of_nodes--;
    }

    void delete_root()
    {
        for(auto& child : root_node->children)
        {
            iterator it = iterator(child);
            erase(it);
        }
        delete root_node;
        root_node = nullptr;
        numer_of_nodes--;
    }

	Node* root_node;
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
            if(node == nullptr) // warunek końcowy
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

	Drzewo(): root_node(nullptr), numer_of_nodes(0){}
    Drzewo(const T& root_value): root_node(new Node(root_value)), numer_of_nodes(1){}
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
		if(parent.ptr == nullptr && root_node == nullptr && index == 0)
        {
            root_node = new Node(value);
            numer_of_nodes++;
            return iterator(root_node);
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


    void erase(const iterator& it)
    {
        if(it.ptr == root_node)
        {
            delete_root();
            numer_of_nodes--;
            return;
        }

        auto begin = it.ptr->parent->children.begin();
        auto end = it.ptr->parent->children.end();
        auto iter = find(begin,end,it.ptr);

        for(auto& child : it.ptr->children)
        {
            delete_node(child);
        }
        it.ptr->parent->children.erase(iter);
        numer_of_nodes--;
    }

    iterator getChild(const iterator& parent, std::size_t index)
    {
        return iterator(parent.ptr->children[index]);
    }

    iterator begin(){ return iterator(root_node); }
    iterator end(){ return iterator(nullptr); }
    iterator root(){ return iterator(root_node); }
    bool empty(){ return numer_of_nodes == 0; }
    std::size_t size() { return numer_of_nodes; }
    int getNumberOfChildren(const iterator& parent){ return parent.ptr->children.size(); }
};

#endif
