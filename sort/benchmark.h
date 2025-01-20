#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

// Функция для замера времени работы функции сортировки
template <typename T>
double measureSortingTime(void (*sortFunction)(T *, unsigned int), T *array, unsigned int size)
{
    auto start = chrono::high_resolution_clock::now();

    sortFunction(array, size);

    auto end = chrono::high_resolution_clock::now();

    // Разница во времени в миллисекундах
    chrono::duration<double> duration = end - start;
    return duration.count();
}

template <typename T>
void generateBestCase(T *array, unsigned int size)
{
    // взрастающая последовательность (наилучший случай)
    for (unsigned int i = 0; i < size; ++i)
    {
        array[i] = i;
    }
}

template <typename T>
void generateWorstCase(T *array, unsigned int size)
{
    // Убывающая последовательность (наихудший случай)
    for (unsigned int i = 0; i < size; ++i)
    {
        array[i] = size - i - 1;
    }
}

template <typename T>
void generateRandomCase(T *array, unsigned int size)
{
    // случайная последовательность (средний случай)
    for (unsigned int i = 0; i < size; ++i)
    {
        array[i] = rand() % 1000;
    }
}

// Функция для записи результатов в CSV файл
void writeToCSV(const string &filename, unsigned int size, double bestTime, double worstTime, double randomTime)
{
    ofstream file;
    file.open(filename, ios::app);

    file << size << "," << bestTime << "," << worstTime << "," << randomTime << "\n";

    file.close();
}

// Функция для тестирования на различных типах данных и измерения времени
template <typename T>
void benchmarkSortingOnSize(void (*sortFunction)(T *, unsigned int), unsigned int size, const string &filename)
{
    // Массивы для различных случаев
    T *bestCase = new T[size];
    T *worstCase = new T[size];
    T *randomCase = new T[size];

    // Генерация разных случаев
    generateBestCase(bestCase, size);
    generateWorstCase(worstCase, size);
    generateRandomCase(randomCase, size);

    double bestTime = measureSortingTime(sortFunction, bestCase, size);

    double worstTime = measureSortingTime(sortFunction, worstCase, size);

    double randomTime = measureSortingTime(sortFunction, randomCase, size);

    // Запись результатов в CSV файл
    writeToCSV(filename, size, bestTime, worstTime, randomTime);

    // Освобождение памяти
    delete[] bestCase;
    delete[] worstCase;
    delete[] randomCase;
}

template <typename T>
void runBenchmark(void (*sortFunction)(T *, unsigned int), string filename)
{

    srand(time(0)); // для случайности данных

    // Размеры массивов для тестирования
    unsigned int sizes[] = {10, 100, 1000, 5000, 10000, 20000};

    // Тестируем на разных размерах и записываем результаты
    for (unsigned int size : sizes)
    {
        benchmarkSortingOnSize(sortFunction, size, filename);
    }

    cout << "Benchmark complete. Filename: " << filename << endl;
}
