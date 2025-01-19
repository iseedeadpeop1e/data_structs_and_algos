//
// Программа демонстрирует использование моей реализации очереди
// для передачи задач обработчику.
//
// Отличается от файла main.cpp только типом используемой очереди (строка 15)

#include <iostream>
#include "my_queue.h"
#include <thread>
#include <mutex>
#include <string>

using namespace std;

typedef MyQueue<string> TaskQueue; // Используемый тип очереди

void printInvite()
{
    cout << "\rEnter a string to worker queue (enter \"exit\" to quit): ";
}

void printQueueStatus(TaskQueue queue)
{
    cout << "\r[STATUS] Current queue status:";
    if (queue.empty())
    {
        cout << " | Queue is empty. |\n";
        return;
    }
    cout << " | Size: " << queue.size() << " | First task to process: " << queue.front() << " | Last task to process: " << queue.back() << " |\n";
}

// Функция - обработчик задач.
// Имитирует выполнение ресурсоемких вычислений.
void worker(TaskQueue &taskQueue, mutex &queueMutex)
{
    string workerTask;

    // Цикл для опрос очереди на предмет наличия задач требующих исполнения.
    while (true)
    {
        if (!taskQueue.empty())
        {
            // Использование мьютекса при помощи lock_guard(освобождает мьютекс при выходе из текущего пространства имен, ограниченного {})
            // Для синхронизации доступа к очереди между главным потоком и потоком-обработчиком.
            {
                lock_guard<mutex> lock(queueMutex);
                workerTask = taskQueue.front();
                try
                {
                    taskQueue.pop();
                }
                catch (overflow_error) // * Для собственной реализации очереди
                {
                    continue;
                }
            }
            if (workerTask == "exit")
                break;
            // Имитация нагрузки
            this_thread::sleep_for(chrono::seconds(3));
            cout << "\n[WORKER] Worker completed task: " << workerTask << "\n";
            printInvite();
        }
    }
}

int main()
{
    // Очередь задач
    TaskQueue taskQueue(10); // Указание размера очереди.
    // Мьютекс для синхронизации доступа
    mutex queueMutex;

    // Запуск потока-обработчика
    // С использованием std::ref() для передачи ссылки на очередь и мьютекс, чтобы обеспечить доступ к этим экземплярам из потока.
    thread workerThread(worker, ref(taskQueue), ref(queueMutex));

    string input;
    while (true)
    {
        {
            lock_guard<mutex> lock(queueMutex);

            // При передаче по значению будет вызван конструктор копирования
            printQueueStatus(taskQueue);
            printInvite();
        }
        cin >> input;
        // Использование мьютекса для синхронизации доступа к очереди
        {
            lock_guard<mutex> lock(queueMutex);
            try
            {
                taskQueue.push(input);
            }
            catch (overflow_error) // Для собственной реализации очереди.
            {
                cout << "\n[WARNING] Queue is full. Try again later.\n";
            }
        }
        if (input == "exit")
            break;
    }
    cout << "\nWaiting for all tasks to complete and exiting...";
    workerThread.join(); // Ожидание завершения исполнения потока-обработчика.
    cout << "\nExited.";
    return 0;
}