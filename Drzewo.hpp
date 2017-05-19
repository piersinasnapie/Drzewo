#ifndef drzewo_hpp
#define drzewo_hpp

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

		Node(const T& _value=T(), Node* _parent=nullptr, Node* _brother=nullptr):
            value(_value),
            parent(_parent),
            brother(_brother)
            {}
		Node(T && _value, Node* _parent=nullptr, Node* _brother=nullptr): 
            value(std::move(_value)), 
            parent(_parent), 
            brother(_brother)
            {}
        // TODO
        ~Node(){}
	};

    void delete_node(Node* node)
    {
        for(Node* child : node->children)
        {
            delete_node(child);
        }

        if(node != root_node)
        {
            if(node->parent->children[0] != node)
            {
                for(Node* child : node->parent->children)
                {
                    if(child->brother == node)
                    {
                        child->brother = node->brother;
                        break;
                    }
                }
            }
        }

        delete node;
        node->children.clear();
        number_of_nodes--;
    }

    void delete_tree()
    {
        if(root_node != nullptr)
        {
            delete_node(root_node);
            root_node = nullptr;
        }
    }

    inline void copy_elements(Node* current_root, Node* other_root, size_t size)
    {
        Node* other_current = other_root;
        Node* current = current_root;
        
        while(number_of_nodes < size)
        {
            if(other_current->children.size())
            {
                for(Node* n : other_current->children)
                {
                    Node* parent = current;
                    T val = n->value;
                    current->children.push_back( new Node(val,parent,nullptr) );
                    number_of_nodes++;
                }
                if(current->children.size() > 1)
                {
                    for(int i=1; i<current->children.size(); i++)
                    {
                        current->children[i-1]->brother = current->children[i];
                    }
                }

                other_current = other_current->children[0];
                current = current->children[0];
            }
            else
            {
                if(other_current->brother != nullptr)
                {
                    other_current = other_current->brother;
                    current = current->brother;
                }
                else
                {
                    other_current = other_current->parent->brother;
                    current = current->parent->brother;
                }
            }
        }
    }

	Node* root_node;
	size_t number_of_nodes;

public:

    typedef T value_type;
    typedef T& reference;

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
            // ptr = next;
            // std::cout << "node: " << ptr->value << std::endl;
            // if(next->children.size() != 0)
            // {
            //     next = next->children[0];
            //     std::cout << "ma dziecko - next: " << next->value << std::endl;
            // }
            // else if(next->brother != nullptr)
            // {
            //     next = next->brother;
            //     std::cout << "ma brata - next: " << next->value << std::endl;
            // }
            // else if(next->brother == nullptr)
            // {
            //     std::cout << "ma tylko rodzica - next: " << next->value << std::endl;
            //     next = next->parent->brother;
            // }
            // else
            // {
            //     next = nullptr;
            // }
            return *this;
        }

        T* operator->()
        {
            return &ptr->value;
        } 

        bool operator!=(const iterator& it){ return this->next != it.next; }
        bool operator==(const iterator& it){ return this->ptr == it.ptr; }
    };

	Drzewo(): root_node(nullptr), number_of_nodes(0){}
    Drzewo(const T& root_value): 
        root_node(new Node(root_value)), 
        number_of_nodes(1) 
        {}

    // TODO
    Drzewo(const Drzewo& other_tree): number_of_nodes(0)
    {
        Node* other_root = other_tree.root().ptr;
        root_node = new Node(other_root->value);        
        number_of_nodes++;

        copy_elements(root_node, other_root, other_tree.size());
    }
    
    Drzewo & operator=(const Drzewo& other_tree)
    {
        if(number_of_nodes)
        {
            delete_tree();
        }

        Node* other_root = other_tree.root().ptr;
        root_node = new Node(other_root->value);        
        number_of_nodes++;

        copy_elements(root_node, other_root, other_tree.size());

        return *this;
    }

    ~Drzewo()
    {
        delete_tree();
    }

	iterator insert(const T& value, iterator parent, std::size_t index)
	{
		if(parent.ptr == nullptr && root_node == nullptr && index == 0)
        {
            root_node = new Node(value);
            number_of_nodes++;
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
			number_of_nodes++;
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

        auto find = std::find(it.ptr->parent->children.begin(),it.ptr->parent->children.end(),it.ptr);
        it.ptr->parent->children.erase(find);
        delete_node(it.ptr);
    }

    iterator getChild(const iterator& parent, std::size_t index)
    {
        return iterator(parent.ptr->children[index]);
    }

    iterator begin() const { return iterator(root_node,root_node); }
    iterator end() const { return iterator(nullptr,nullptr); }
    iterator root() const { return iterator(root_node); }
    bool empty(){ return number_of_nodes == 0; }
    std::size_t size() const { return number_of_nodes; }
    int getNumberOfChildren(const iterator& parent){ return parent.ptr->children.size(); }
};

#endif
