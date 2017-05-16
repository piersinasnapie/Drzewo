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
        Node* brother;
		std::vector<Node*> children; // list of children
        // int current_child;

		Node(const T& _value=T(), Node* _parent=nullptr, Node* _brother=nullptr):
            value(_value),
            parent(_parent),
            brother(_brother)
            // current_child(_current)
            {}
		Node(T && _value, Node* _parent=nullptr, Node* _brother=nullptr): 
            value(std::move(_value)), 
            parent(_parent), 
            brother(_brother)
            {}
        // TODO
        ~Node()
        {}
	};

    void delete_node(Node* node)
    {
        for(Node* child : node->children)
        {
            delete_node(child);
        }
        if(node->parent->children[0] != node)
        {
            for(Node* child : node->parent->children)
            {
                if(child->brother == node)
                {
                    child->brother = node->brother;
                }
            }
        }
        delete node;
        node->children.clear();
        numer_of_nodes--;
    }

    void delete_tree()
    {
        if(root_node != nullptr)
        {
            delete_node(root_node);
            root_node = nullptr;
        }
    }

	Node* root_node;
	size_t numer_of_nodes;

public:

    typedef T value_type;
    typedef T& reference;

	// class iterator
 //    {
 //    private:

 //    	Node* ptr;
 //        friend class Drzewo;

 //        // PRE-ORDER
 //        Node* traverse(Node* node)
 //        {
 //            if(node == nullptr) // warunek końcowy
 //            {
 //                return node;
 //            }
 //            if(node->current_child == node->children.size())
 //            {
 //                node->current_child = 0;
 //                return traverse(node->parent);
 //            }
 //            if(node->children.size() != 0)
 //            {
 //                int index = node->current_child;
 //                node->current_child++;
 //                return node->children[index];
 //            }
 //            return traverse(node);
 //        }

 //        iterator(Node* node): ptr(node){}

 //    public:

 //        typedef T value_type;

 //    	iterator(): ptr(nullptr){}
 //    	iterator(const iterator& iterator): ptr(iterator.ptr){}
 //        T& operator*(){ return ptr->value; }

 //        iterator& operator++()
 //        {
 //    		ptr = traverse(ptr);
 //            return *this;
 //        }

 //        bool operator!=(const iterator& it){ return this->ptr != it.ptr; }
 //        bool operator==(const iterator& it){ return this->ptr == it.ptr; }

 //        // T* operator->(){ return &ptr; }
 //    };

    class iterator
    {
    private:
        Node* ptr;
        Node* next;
        friend class Drzewo;

        iterator(Node* _ptr=nullptr, Node* _next=nullptr): 
            ptr(_ptr),
            next(_next)
            {}

    public:

        typedef T value_type;

        iterator(): ptr(nullptr){}
        iterator(const iterator& iterator): ptr(iterator.ptr){}
        T& operator*(){ return ptr->value; }

        iterator& operator++()
        {
            ptr = next;
            std::cout << "node: " << ptr->value << std::endl;
            if(next->children.size() != 0)
            {
                next = next->children[0];
                std::cout << "ma dziecko - next: " << next->value << std::endl;
            }
            else if(next->brother != nullptr)
            {
                next = next->brother;
                std::cout << "ma brata - next: " << next->value << std::endl;
            }
            else if(next->brother == nullptr)
            {
                std::cout << "ma tylko rodzica - next: " << next->value << std::endl;
                next = next->parent->brother;
            }
            else
            {
                next = nullptr;
            }
            return *this;
        }

        bool operator!=(const iterator& it){ return this->next != it.next; }
        bool operator==(const iterator& it){ return this->ptr == it.ptr; }
    };

	Drzewo(): root_node(nullptr), numer_of_nodes(0){}
    Drzewo(const T& root_value): 
        root_node(new Node(root_value)), 
        numer_of_nodes(1) 
        {}

    // TODO
    Drzewo(const Drzewo& other_tree)
    {
        Node* other_root = other_tree.root().ptr;
        root_node = new Node(other_root->value);        
        numer_of_nodes++;

        Node* current = other_root;
        Node* node = root_node;

        for(const Node* n : current->children)
        {
            T value = n->value;
            node->children.push_back(new Node(value));
        }
    }

    // TODO
    Drzewo & operator=(const Drzewo& other_tree);
    ~Drzewo()
    {
        // delete_tree();
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
            size_t children_size = children->size();
			if(index >= children_size) // czy ma sens ?
			{
                if(children_size != 0)
                {
                    children->at(children_size-1)->brother = node;
                }
				children->push_back(node);
			}
            else
			{
                node->brother = children->at(index);
				children->insert(children->begin()+index,node);
                if(index != 0)
                {
                   children->at(index-1)->brother = node;
                }
			}
			numer_of_nodes++;
			return iterator(node);
		}
	}

    void erase(const iterator& it)
    {
        if(it.ptr == root_node)
        {
            delete_node(it.ptr);
            root_node = nullptr;
            return;
        }
        int position = it.ptr - it.ptr->parent->children[0];
        it.ptr->parent->children.erase(it.ptr->parent->children.begin() + position);
        delete_node(it.ptr);
    }

    iterator getChild(const iterator& parent, std::size_t index)
    {
        return iterator(parent.ptr->children[index]);
    }

    iterator begin() const { return iterator(root_node,root_node); }
    iterator end() const { return iterator(nullptr,nullptr); }
    iterator root() const { return iterator(root_node); }
    bool empty(){ return numer_of_nodes == 0; }
    std::size_t size() const { return numer_of_nodes; }
    int getNumberOfChildren(const iterator& parent){ return parent.ptr->children.size(); }
};

#endif
