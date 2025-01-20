#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// Шаблонная функция для проверки отсортированного массива
template <typename T>
bool isSorted(const T *array, unsigned int size)
{
    for (unsigned int i = 1; i < size; ++i)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}

// Шаблонная функция для тестирования сортировки
template <typename T>
void testSorting(void (*sortFunction)(T *, unsigned int))
{

    // Случайные значения
    const unsigned int randomSize = 100;
    T randomArray[randomSize];
    srand(time(nullptr)); // Для случайности элементов
    for (unsigned int i = 0; i < randomSize; ++i)
    {
        randomArray[i] = static_cast<T>(rand() % 100);
    }
    sortFunction(randomArray, randomSize);
    assert(isSorted(randomArray, randomSize));

    // Возрастающая последовательность
    const unsigned int testArraySize = 5;
    T ascendingArray[testArraySize] = {1, 2, 3, 4, 5};
    sortFunction(ascendingArray, testArraySize);
    assert(isSorted(ascendingArray, testArraySize));

    // Убывающая последовательность
    T descendingArray[testArraySize] = {5, 4, 3, 2, 1};
    sortFunction(descendingArray, testArraySize);
    assert(isSorted(descendingArray, testArraySize));

    // Последовательность с повторяющимися элементами
    T repeatingArray[testArraySize] = {3, 3, 2, 2, 1};
    sortFunction(repeatingArray, testArraySize);
    assert(isSorted(repeatingArray, testArraySize));

    // Последовательность из одинаковых элементов
    T sameArray[testArraySize] = {4, 4, 4, 4, 4};
    sortFunction(sameArray, testArraySize);
    assert(isSorted(sameArray, testArraySize));

    // Последовательность с чётным количеством элементов
    const unsigned int evenSize = 6;
    T evenArray[evenSize] = {6, 3, 8, 1, 5, 2};
    sortFunction(evenArray, evenSize);
    assert(isSorted(evenArray, evenSize));

    // Последовательность с нечётным количеством элементов
    const unsigned int oddSize = 7;
    T oddArray[oddSize] = {7, 3, 8, 1, 5, 2, 4};
    sortFunction(oddArray, oddSize);
    assert(isSorted(oddArray, oddSize));

    // Пустая последовательность
    T emptyArray[0] = {};
    sortFunction(emptyArray, 0);
    assert(isSorted(emptyArray, 0));

    // Последовательность из одного элемента
    T singleArray[1] = {42};
    sortFunction(singleArray, 1);
    assert(isSorted(singleArray, 1));

    // 1Последовательность из двух элементов
    T twoArray[2] = {7, 3};
    sortFunction(twoArray, 2);
    assert(isSorted(twoArray, 2));

    cout << "Passed all tests!\n";
}
