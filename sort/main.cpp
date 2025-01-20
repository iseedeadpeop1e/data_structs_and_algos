#include <iostream>
#include "testsorting.h"
#include "simple_sort.h"
#include "benchmark.h"

using namespace std;

const unsigned int SEED = 5;
const unsigned int SIZE = 11;

// Алгоритм быстрой сортировки
template <typename T>
void quickSort(T *arr, int left, int right)
{
    // если подмассив пуст или содержит один элемент, выходим
    if (left >= right)
    {
        return;
    }

    // Выбор опорного элемента
    int pivotIndex = left + rand() % (right - left + 1);
    swap(arr[pivotIndex], arr[left]); // Меняем опорный с первым элементом
    T pivot = arr[left];              // Запоминаем значение опорного элемента

    int lt = left - 1;  // Индекс конца области < pivot
    int i = left;       // Текущий индекс просмотра
    int gt = right + 1; // Индекс начала области > pivot

    while (i < gt)
    {
        if (arr[i] < pivot)
        // Если текущий элемент меньше опорного:
        // - Меняем местами arr[i] и arr[lt + 1] (перемещаем в область < pivot)
        // - Увеличиваем lt и i
        {
            ++lt;
            swap(arr[lt], arr[i]);
            ++i;
        }
        else if (!(pivot < arr[i]))
        { // arr[i] == pivot
            // Если текущий элемент равен опорному:
            // - Просто увеличиваем i (оставляем на месте)
            i++;
        }
        else
        { // pivot < arr[i]
            // Если текущий элемент больше опорного:
            // - Меняем местами arr[i] и arr[gt - 1] (перемещаем в область > pivot)
            // - Уменьшаем gt
            --gt;
            swap(arr[i], arr[gt]);
            // i не увеличиваем, так как на место arr[i] мог попасть неотсортированный элемент
        }
    }
    // Сортируем левую часть
    quickSort(arr, left, lt);
    // Сортируем правую часть
    quickSort(arr, gt, right);
}

template <typename T>
void quickSort(T *array, unsigned int size)
{
    quickSort(array, 0, size - 1);
}

// Вывод массива в консоль
template <typename T>
void printArray(T *array, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << array[i] << ", ";
    }
    cout << "\n";
}

int main()
{
    srand(SEED);
    double randomArray[SIZE] = {0};

    for (int i = 0; i < SIZE; ++i)
    {
        randomArray[i] = rand() % 100;
    }

    printArray(randomArray, SIZE);
    // cocktailSort(randomArray, SIZE);
    // selectionSort(randomArray, SIZE);
    // insertionSort(randomArray, SIZE);
    quickSort(randomArray, SIZE);
    printArray(randomArray, SIZE);

    // Тестируем алгоритмы сортировки
    testSorting<double>(cocktailSort);
    testSorting<double>(selectionSort);
    testSorting<double>(insertionSort);
    testSorting<double>(quickSort);

    // Замеряем время алгоритмов сортировки
    runBenchmark<double>(cocktailSort, "cocktailSort.csv");
    runBenchmark<double>(selectionSort, "selectionSort.csv");
    runBenchmark<double>(insertionSort, "insertionSort.csv");
    runBenchmark<double>(quickSort, "quickSort.csv");
}