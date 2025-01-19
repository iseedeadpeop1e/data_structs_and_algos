// В рамках примера, код реализации методов находится в заголовочном файле, для упрощения просмотра.

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template <typename T>
class MyQueue
{
private:
    T *container;
    size_t capacity;
    size_t front_inx;
    size_t back_inx;
    size_t items_count;

public:
    // Конструктор
    MyQueue(size_t size) : capacity(size), front_inx(0), back_inx(0), items_count(0)
    {
        container = new T[size];
    }
    // Деструктор
    ~MyQueue()
    {
        delete[] container; // освобождаем выделенную память
    }

    // Конструктор копирования
    MyQueue(const MyQueue &otherQueue)
    {
        capacity = otherQueue.capacity;
        front_inx = otherQueue.front_inx;
        back_inx = otherQueue.back_inx;
        items_count = otherQueue.items_count;

        container = new T[otherQueue.capacity];
        // Копируем элементы
        for (size_t i = 0; i < capacity; ++i)
        {
            container[i] = otherQueue.container[i];
        }
    }

    size_t size() const
    {
        return items_count;
    }

    bool empty() const
    {
        return items_count == 0;
    }

    T front() const
    {
        return container[front_inx];
    }

    T back() const
    {
        return container[back_inx];
    }

    void push(const T &element)
    {
        if (items_count == capacity)
        {
            throw overflow_error("Queue is full.");
        }
        back_inx = (back_inx + 1) % capacity;
        container[back_inx] = element;
        items_count++;
    }

    void pop()
    {
        if (items_count == 0)
        {
            throw overflow_error("Queue is empty.");
        }
        front_inx = (front_inx + 1) % capacity;
        items_count--;
    }

    bool full()
    {
        return items_count == capacity;
    }
};

#endif