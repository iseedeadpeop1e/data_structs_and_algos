import matplotlib.pyplot as plt
import csv

def read_benchmark_data(filename):
    sizes = []
    best_case_times = []
    worst_case_times = []
    random_case_times = []

    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            sizes.append(int(row[0]))
            best_case_times.append(float(row[1]))
            worst_case_times.append(float(row[2]))
            random_case_times.append(float(row[3]))

    return sizes, best_case_times, worst_case_times, random_case_times

def plot_benchmark_results(sizes, best_case_times, worst_case_times, random_case_times, output_filename):
    plt.figure(figsize=(10, 6))

    plt.plot(sizes, best_case_times, marker='o', label='Наилучший случай')
    plt.plot(sizes, worst_case_times, marker='o', label='Наихудший случай')
    plt.plot(sizes, random_case_times, marker='o', label='Случайный случай')

    plt.title('Время выполнения сортировки', fontsize=14)
    plt.xlabel('Размер массива', fontsize=12)
    plt.ylabel('Время (секунды)', fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend(fontsize=12)
    plt.tight_layout()

    plt.savefig(output_filename)
    plt.close()

def main():
    # Имя CSV файла с результатами бенчмарка
    filenames = ['cocktailSort.csv', 'insertionSort.csv', 'quickSort.csv', 'selectionSort.csv']

    for filename in filenames:
        # Имя файла для сохранения графика
        output_filename = filename[:-4] + '.png'

        sizes, best_case_times, worst_case_times, random_case_times = read_benchmark_data(filename)

        plot_benchmark_results(sizes, best_case_times, worst_case_times, random_case_times, output_filename)

        print(f'График успешно сохранён в файл {output_filename}')

if __name__ == '__main__':
    main()
