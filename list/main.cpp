#include "LinkedList.h"

using namespace std;
// Демонстрация использования
int main()
{
    LinkedList<int> list;

    // Добавление элементов
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    cout << "After push: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // Удаление элементов
    list.pop_front();
    list.pop_back();
    cout << "After pop: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // Вставка в произвольное место
    list.push_back(3);
    list.push_back(4);
    auto it = list.begin();
    ++it; // Переместиться ко второму элементу
    list.insert(it, 99);
    cout << "After insert: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // Удаление произвольного элемента
    list.erase(it);
    cout << "After erase: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // Копирование и присваивание
    LinkedList<int> copy = list;
    cout << "Copy : ";
    for (auto it = copy.begin(); it != copy.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // Изменение начального элемента 
    list.front() += 5;
    cout << "After change: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";


    return 0;
}