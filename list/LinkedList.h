// Ниже представлен шаблон класса, реализующего двусвязный список.
// В рамках примера, код реализации методов находится в заголовочном файле, для упрощения просмотра.

#include <iostream>

template <typename T>
class LinkedList
{
private:
    // Единица хранения данных в списке, "узел".
    // Хранит в себе ссылки на следующий и предыдущий узлы.
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        Node(T item) : data(item), prev(nullptr), next(nullptr) {}
    };

    Node *head; // Указатель на начало списка
    Node *tail; // Указатель на конец списка
    size_t nodes_count; // Количество элементов списка

    void clear()
    {
        while (head != nullptr)
        {
            pop_front();
        }
    }

        // Вставка элемента перед указанным узлом
    void insert(Node *pos, const T &data)
    {
        if (pos == nullptr)
            throw std::invalid_argument("Position cannot be null");

        Node *new_node = new Node(data);
        new_node->next = pos;
        new_node->prev = pos->prev;

        if (pos->prev != nullptr)
            pos->prev->next = new_node;
        else
            head = new_node;

        pos->prev = new_node;
        nodes_count++;
    }

        // Удаление указанного узла
    void erase(Node *pos)
    {
        if (pos == nullptr)
            throw std::invalid_argument("Position cannot be null");

        if (pos->prev != nullptr)
            pos->prev->next = pos->next;
        else
            head = pos->next;

        if (pos->next != nullptr)
            pos->next->prev = pos->prev;
        else
            tail = pos->prev;

        delete pos;
        nodes_count--;
    }

public:
    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr), nodes_count(0) {}

    // Конструктор копирования
    LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), nodes_count(0)
    {
        Node *current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания
    LinkedList &operator=(const LinkedList &other)
    {
        if (this == &other)
            return *this;

        clear();
        Node *current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
        return *this;
    }

    // Деструктор
    ~LinkedList()
    {
        clear();
    }

    // Размер списка
    size_t size() const
    {
        return nodes_count;
    }


    // Доступы вощвращают ссылку на данные узла, 
    // чтобы обеспечить возиожность их изменять
    
    // Доступ к начальному элементу
    T &front()
    {
        if (head == nullptr)
            throw std::out_of_range("List is empty");
        return head->data;
    }

    // Доступ к конечному элементу
    T &back()
    {
        if (tail == nullptr)
            throw std::out_of_range("List is empty");
        return tail->data;
    }

    // Добавление элемента в начало
    void push_front(const T &data)
    {
        Node *ptr = new Node(data);

        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;
        if (tail == nullptr)
            tail = ptr;
        head = ptr;
        nodes_count++;
    }

    // Добавление элемента в конец
    void push_back(const T &data)
    {
        Node *ptr = new Node(data);

        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;
        if (head == nullptr)
            head = ptr;
        tail = ptr;
        nodes_count++;
    }

    // Удаление элемента из начала
    void pop_front()
    {
        if (head == nullptr)
            return;

        Node *ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;

        delete head;
        head = ptr;
        nodes_count--;
    }

    // Удаление элемента из конца
    void pop_back()
    {
        if (tail == nullptr)
            return;

        Node *ptr = tail->prev;
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;

        delete tail;
        tail = ptr;
        nodes_count--;
    }

    // Итератор
    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *node) : current(node) {}

        T &operator*() { return current->data; }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }


        // Метод для получения ссылки на узел. 
        // Используется для операций вставки и удаления в списке
        Node *getNode()
        {
            return current;
        }
    };

    Iterator begin() { return Iterator(head); }

    Iterator end() { return Iterator(nullptr); }


    // Вставка элемента перед указанным узлом по итератору
    void insert(Iterator pos_it, const T &data)
    {
        insert(pos_it.getNode(), data);
    }

    // Удаление элемента по итератору
    void erase(Iterator pos_it)
    {
        erase(pos_it.getNode());
    }
    
};
