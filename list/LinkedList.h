template <typename T>
class Node
{
public:
    T data;
    Node *prev;
    Node *next;

    Node(T item) : data(item), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node *head;
    Node *tail;
    size_t nodes_count;

public:
    void size() const
    {
        return nodes_count;
    }

    void push_front(const T &data)
    {
        Node *ptr = new Node(data);

        ptr.next = head;
        if (head != NULL)
            head.prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;

        return ptr;
    }

    void push_back(const T &data)
    {
        Node *ptr = new Node(data);

        ptr.prev = tail;
        if (tail != NULL)
            tail.next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;

        return ptr;
    }
};