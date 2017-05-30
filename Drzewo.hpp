#ifndef drzewo_hpp
#define drzewo_hpp

#include <vector>
#include <algorithm>

/**
 * \class Drzewo
 *
 * Kontener reprezentujący strukturę danych - Drzewo. Posiada korzeń, który jest jednocześnie
 * węzłem/elementem w kontenerze. Istnieje możliwość utworzenia pustego drzewa. 
 * Dostęp do elementów kontenera jest udostępniony za pomocą pomocniczych
 * obiektów klasy iterator. 
 *
 */
template<typename T>
class Drzewo
{
private:

    /** 
     * Struktura reprezentująca pojedyczny wezeł w drzewie.
     * Zawiera w sobie:
     *  - Obiekt typu T
     *  - wskaźnik do węzła będącego rodzicem
     *  - wskaźnik do węzłą będącego bratem
     *  - listę dzieci uporządkowaną w wektor
     */
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
                    while(other_current->parent->brother == nullptr)
                    {
                        other_current = other_current->parent;
                        current = current->parent;
                    }
                    other_current = other_current->parent->brother;
                    current = current->parent->brother;
                }
            }
        }
    }

	Node* root_node;
	size_t number_of_nodes;

public:

    /** T */
    typedef T value_type; 
    /** value_type& */
    typedef T& reference; 

    /**
     * \class iterator
     *
     * Klasa pomocnicza reprezentująca wskaźnik na pojedyczny element w kontenerze.
     * Za pomocą obiektów klasy iterator użytkownik biblioteki posiada możliwość
     * wykonywania pewnych operacji. 
     */
    class iterator
    {
    private:

        Node* ptr;
        friend class Drzewo;

        iterator(Node* _ptr=nullptr): 
            ptr(_ptr)
            {}

    public:

        /** T */
        typedef T value_type; 

        /**
         * Konstruktor domyślny tworzący iterator pokazujący na koniec kontenera.
         * 
         */
        inline iterator();

        /**
         * Konstruktor kopiujący ustawiający wartość wskaźnika na 
         * wskaźnik iteratora przesłanego do konstruktora.
         *
         * @param  iterator iterator, którego wskaźnik zostanie skopiowany. 
         */
        inline iterator(const iterator& iterator);
        
        /**
         * Zwraca referencję do obiektu typu przechowywanego w pojedynczym węźle,
         * wskazywanym przez iterator.
         *
         * @return  referencja do obiektu typu T
         */
        inline T& operator*();

        /**
         * Operator pre-inkrementacji dla klasy iterator.
         * Przechodzenie po drzewie następuje w porządku:
         * PRE-ORDER. Zwraca referencję do samego siebie (obiektu klasy iterator).
         * 
         * @return  Wskaźnik do samego siebie.
         */
        iterator& operator++();

        /**
         * Operator post-inkrementacji dla klasy iterator.
         * Przechodzenie po drzewie następuje w porządku:
         * PRE-ORDER. Zwraca referencję do samego siebie (obiektu klasy iterator).
         * 
         * @return  Wskaźnik do samego siebie.
         */
        iterator& operator++(int);

        /**
         * Zwraca adres do obiektu typu T przechowywanego we wskaźniku.
         * 
         * @return adres obiektu typu T
         */
        inline T* operator->();

        /**
         * Zwraca 'true' jeśli iterator pokazuje na inny węzeł niż 
         * iterator przesyłany do funkcji.
         *
         * @return  true - gdy obiekty na które pokazują iteratory są różne, flase - gdy obiekty na które pokazują iteratory są równe
         */
        inline bool operator!=(const iterator& it) const;

        /**
         * Zwraca 'true' jeśli iterator pokazuje na ten sam węzeł niż 
         * iterator przesyłany do funkcji.
         *
         * @return  true - gdy obiekty na które pokazują iteratory są równe, flase - gdy obiekty na które pokazują iteratory są różne
         */
        inline bool operator==(const iterator& it) const;
    };

    /** 
     * Konstruktor domyślny. Inicjuje wkaźnik do korzenia na 'nullptr'. 
     * Nowo utworzone drzewo posiada 0 węzłów. 
     * Zostanie utworzone puste drzewo. 
     *
     */
	Drzewo();

    /**
     * Konstruktor inicjujący korzeń drzewa wartością 'root_vale'.
     * Zostanie utworzone drzewo z jednym węzłem.
     *
     * @param  root_value obiekt typu T.
     */
    Drzewo(const T& root_value);

    /**
     * Konstruktor kopiujący, przyjmujący stałą referencję do obiektu klasy Drzewo.
     * Wszystkie elementy drzewa kopiowanego zostają dodane do obecnie tworzonego drzewa,
     * zachowując porządek, kolejność oraz hierarchię węzłów w kopiowanym drzewie.
     *
     * @param  other_tree obiekt klasy Drzewo<>.
     */
    Drzewo(const Drzewo& other_tree);

    /**
     * Operator przypisania drzewa. Przypisuje wszystkie elementy kopiowanego drzewa
     * do obecnie tworzonego drzewa. Jeśli obecne drzewo nie jest puste, następuje wyczyszczenie
     * wszystkich elementów drzewa, a następnie zostają kopiowane elementy z drugiego drzewa.
     * W przypadku wykonania operacji na pustych drzewach zostanie zwrócone puste drzewo.
     *
     * @param other_tree obiekt klasy Drzewo<>.
     */
    Drzewo & operator=(const Drzewo& other_tree);

    /**
     * Destruktor, zwalnia pamięć, która była używana przez drzewo.
     * Usuwa wszystkie informacje zawarte w pojedynczych węzłach drzewa.
     *
     */
    ~Drzewo();

    /**
     * Wstawia element o podanej wartości do drzewa, do listy dzieci rodzica, wskazywanego
     * przez iterator, na określoną przez indeks pozycję. Zwraca iterator pokazujący na 
     * nowo dodany węzeł. W przypadku pustego drzewa oraz podania iteratora wskazującego na koniec kontenera
     * oraz indexu równego '0' zostanie utworzony korzeń zawierający obiekt 'value'. Zwrócony zostanie iterator
     * pokazujący na korzeń drzewa.
     * 
     * W przypadku wywołania procedury insert z argumentami: iterator pokazujący na koniec oraz indexem równym 0,
     * na niepustym drzewie zachowanie funkcji jest niezdefiniowane. 
     *
     * W przypadku podania iteratora wskazującego na koniec kontenera oraz indeksu różnego 
     * od 0 operacja skutkuje niezdefiniowanym zachowaniem.
     * 
     * W pozostałych przypadkach element o wartości 'value' zostanie wstawiony
     * do listy dzieci węzła-rodzica pokazywanego przez iterator przed węzeł znajdujący się
     * na miejscu nr 'index'.
     * Na koniec procedury zostanie zwiększona liczba elementów w drzewie. 
     *  
     * @param  value  obiekt typu T
     * @param  parent iterator pokazujący na węzeł-rodzic
     * @param  index  numer pozycji na liście dzieci rodzica
     * @return  iterator pokazujący na nowo wstawiony węzeł
     */
	iterator insert(const T& value, iterator parent, std::size_t index);

    /**
     * Usuwa z drzewa element pokazywany przez iterator. W pierwszej kolejności 
     * zostaną usunięte wszystkie dzieci podanego węzła - dealokacja pamięci.
     * Jeśli dany węzeł posiada wiele poziomów dzieci, to zostaną najpierw usunięte wszystkie
     * dzieci na najniższym poziomie drzewa, a następnie ich rodzice. Na końcu zostanie usunięty 
     * węzeł pokazywany przez iterator. W przypadku podania iteratora wskazującego na koniec
     * kontenera zachowanie operacji jest niezdefiniowane. 
     * 
     * @param  it iterator pokazujący na węzeł przeznaczony do usunięcia.
     */
    void erase(const iterator& it);

    /**
     * Zwraca iterator pokazujący na dziecko znajdujące się w liście dzieci węzła-rodzica wskazanego przez
     * iterator, na miejscu o podanym indeksie. 
     * 
     * W przypadku podania iteratora wskazującego
     * na koniec kontenera operacja skutkuje niezdefiniowanym zachowaniem. 
     * 
     * W przypaku podania nieprawidłowego indeksu dziecka operacja skutkuje 
     * niezdefiniowanym zachowaniem.
     * 
     * @param  parent iterator na wezeł-rodzica
     * @param  index pozycja dziecka w liście dzieci rodzica
     * @return  iterator pokazujący na dziecko znajdujące się na danej pozycji
     */
    inline iterator getChild(const iterator& parent, std::size_t index);

    /**
     * Zwraca iterator pokazujący na pierwszy element w drzewie - korzeń drzewa.
     * 
     * @return  iterator pokazujący na pierwszy element w drzewie.
     */
    inline iterator begin() const;

    /**
     * Zwraca iterator pokazujący na element za ostatnim elementem w drzewie.
     * Pokazuje na rodzica(węzeł) korzenia, który jest wskaźnikiem na 'nullptr'.
     * 
     * @return  iterator  
     */
    inline iterator end() const;

    /**
     * Zwraca iterator pokazujący na korzeń drzewa.
     * 
     * @return  iterator pokazujący na korzeń drzewa.
     */
    inline iterator root() const;

    /**
     * Zwraca wartość 'true' jeśli ilość węzłów w drzewie wynosi 0.
     * 
     * @return  true - jeżeli liczba węzłów w drzewie równa się 0 false - jeżeli liczba węzłów w drzwie jest większa od 0
     */
    inline bool empty() const;

    /**
     * Zwraca liczbę elementów występujących w drzewie.
     * 
     * @return  Liczba węzłów w drzewie.
     */
    inline std::size_t size() const;

    /**
     * Zwraca liczbę 'bezpośrednich' (znajdujących się bezpośrednio poziom pod danym węzłem) 
     * dzieci danego węzła, na który pokazuje iterator. 
     * 
     * W przypadku podania iteratora pokazującego
     * na koniec kontenera operacja skutkuje niezdefiniowanym zachowaniem.
     * 
     * @param  parent iterator pokazujący na węzeł.
     * @return  liczba węzłów-dzieci podanego rodzica.
     */
    inline int getNumberOfChildren(const iterator& parent);
};

/*







    DRZEWO






 */

template<typename T>
Drzewo<T>::Drzewo()
{
    root_node = nullptr;
    number_of_nodes = 0;
}

template<typename T>
Drzewo<T>::Drzewo(const T& root_value)
{
    root_node = new Node( root_value );
    number_of_nodes = 1;
}

template<typename T>
Drzewo<T>::Drzewo(const Drzewo& other_tree)
{
    number_of_nodes = 0;
    if(other_tree.root().ptr != nullptr)
    {
        Node* other_root = other_tree.root().ptr;
        root_node = new Node(other_root->value);        
        number_of_nodes++;

        copy_elements(root_node, other_root, other_tree.size());
    }
}

template<typename T>
Drzewo<T>& Drzewo<T>::operator=(const Drzewo& other_tree)
{
    if(other_tree.root().ptr != nullptr)
    {
        if(number_of_nodes)
        {
            delete_tree();
        }

        Node* other_root = other_tree.root().ptr;
        root_node = new Node(other_root->value);        
        number_of_nodes++;

        copy_elements(root_node, other_root, other_tree.size());
    }
    return *this;
}

template<typename T>
Drzewo<T>::~Drzewo()
{
    delete_tree();
}

template<typename T>
typename Drzewo<T>::iterator Drzewo<T>::insert(const T& value, iterator parent, std::size_t index)
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
        if(index >= children_size)
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
    
template<typename T>
void Drzewo<T>::erase(const iterator& it)
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

template<typename T>
inline typename Drzewo<T>::iterator Drzewo<T>::getChild(const iterator& parent, std::size_t index)
{
    return iterator(parent.ptr->children[index]);
}

template<typename T>
inline typename Drzewo<T>::iterator Drzewo<T>::begin() const 
{
    return iterator(root_node); 
}

template<typename T>
inline typename Drzewo<T>::iterator Drzewo<T>::end() const 
{ 
    return iterator(nullptr); 
}

template<typename T>
inline typename Drzewo<T>::iterator Drzewo<T>::root() const 
{ 
    return iterator(root_node); 
}

template<typename T>
inline bool Drzewo<T>::empty() const
{ 
    return number_of_nodes == 0; 
}

template<typename T>
inline std::size_t Drzewo<T>::size() const 
{ 
    return number_of_nodes; 
}

template<typename T>
inline int Drzewo<T>::getNumberOfChildren(const iterator& parent)
{ 
    return parent.ptr->children.size(); 
}

/*







    ITERATOR






 */

template<typename T>
inline Drzewo<T>::iterator::iterator()
{
    ptr = nullptr;
}

template<typename T>
inline Drzewo<T>::iterator::iterator(const iterator& iterator)
{
    ptr = iterator.ptr;
}

template<typename T>
inline T& Drzewo<T>::iterator::operator*()
{ 
    return ptr->value; 
}

template<typename T>
inline bool Drzewo<T>::iterator::operator!=(const iterator& it) const
{ 
    return this->ptr != it.ptr; 
}

template<typename T>
inline bool Drzewo<T>::iterator::operator==(const iterator& it) const
{ 
    return this->ptr == it.ptr; 
}

template<typename T>
inline T* Drzewo<T>::iterator::operator->()
{
    return &(ptr->value);
}

template<typename T>
typename Drzewo<T>::iterator& Drzewo<T>::iterator::operator++()
{
    if(ptr->children.size())
    {
        this->ptr = ptr->children[0];
    }
    else if(ptr->brother != nullptr)
    {
        ptr = ptr->brother;
    }
    else
    {
        while(ptr->parent->brother == nullptr)
        {
            ptr = ptr->parent;
            if(ptr->parent == nullptr)
            {
                ptr = ptr->parent;
                return *this;
            }
        }
        ptr = ptr->parent->brother;
    }
    return *this;
}

template<typename T>
typename Drzewo<T>::iterator& Drzewo<T>::iterator::operator++(int)
{
    return operator++();
}


#endif
