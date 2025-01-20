
// Шейкерная сортировка
template <typename T>
void cocktailSort(T *array, unsigned int size)
{
    bool swapped = true; // устанавливаем значение флага в true, чтобы инициировать первый проход по массиву.
    int start = 0;
    int end = size - 1;

    while (swapped) // Выполняем проходы по массиву, пока происходит хотя бы одна перестановка за проход.
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (array[i + 1] < array[i])
            {
                swap(array[i], array[i + 1]);
                swapped = true; // Произошла перестановка
            }
        }

        if (!swapped)
            break; // Если перестановок совершено не было, массив отсортирован.

        --end; // Сдвигаем конец рабочей области на единицу влево, так как максимальный элемент в текущей уже на своем месте.

        swapped = false; // Устанавливаем значение флага false, чтобы применить его к проходу в обратном порядке.

        for (int i = end; i > start; --i)
        {
            if (array[i] < array[i - 1])
            {
                swap(array[i], array[i - 1]);
                swapped = true;
            }
        }

        ++start; // Сдвигаем начало рабочей области на единицу вправо, так как минимальный элемент в текущей уже на своем месте.
    }
}

// Сортировка выбором
template <typename T>
void selectionSort(T *array, unsigned int size)
{
    int start = 0;
    int end = size - 1;

    int min_inx = 0;
    int max_inx = 0;

    while (start < end)
    {
        min_inx = start;
        max_inx = start;
        for (int i = start + 1; i <= end; ++i)
        {
            if (array[i] < array[min_inx])
            {
                min_inx = i;
            }
            if (array[max_inx] < array[i])
            {
                max_inx = i;
            }
        }
        // Перемещаем минимальный элемент на место start
        swap(array[min_inx], array[start]);

        // Если максимальный элемент был на месте start, нужно обновить max_inx
        if (max_inx == start)
        {
            max_inx = min_inx;
        }
        // Перемещаем максимальынй элемент на место end
        swap(array[max_inx], array[end]);
        ++start;
        --end;
    }
}

// Сортировка вставками
template <typename T>
void insertionSort(T *array, unsigned int size)
{
    for (int i = 1; i < size; ++i)
    {
        T item = array[i]; // Первый элемент считаем отсортированным
        int moving_inx = i - 1;
        while (moving_inx >= 0 && item < array[moving_inx])
        {
            // Сдвигаем большие элементы вправо
            array[moving_inx + 1] = array[moving_inx];
            --moving_inx;
        }
        array[moving_inx + 1] = item;
    }
}
