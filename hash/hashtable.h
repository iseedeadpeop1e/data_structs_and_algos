#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

template <typename ValueType>
class HashTable {  
    private:
        size_t hashGroups;
        size_t itemsCount;
        list<pair<size_t, ValueType>> *table = nullptr;
    
    public:

        HashTable(size_t hashGroups) : hashGroups(hashGroups) {
            table = new list<pair<size_t, ValueType>>[hashGroups];
        }

        // конструктор копирования
        HashTable(const HashTable& other) : hashGroups(other.hashGroups), itemsCount(other.itemsCount) {
            table = new list<pair<size_t, ValueType>>[hashGroups]; 
            for (size_t i = 0; i < hashGroups; ++i) {
                table[i] = other.table[i]; 
            }
        }

        ~HashTable() {
            for (size_t i = 0; i < hashGroups; ++i) {
                table[i].clear();
            }

            delete[] table;
        }
        
        // присваивание
        HashTable& operator=(const HashTable& other) {
            if (this != &other) { 
                
                //очиста предыдущих данных 
                for (size_t i = 0; i < hashGroups; ++i) {
                    table[i].clear();
                }
                delete[] table;
        
                hashGroups = other.hashGroups;
                itemsCount = other.itemsCount;
                table = new list<pair<size_t, ValueType>>[hashGroups];
                for (size_t i = 0; i < hashGroups; ++i) {
                    table[i] = other.table[i];
                }
            }
            return *this; 
        }

        bool isEmpty() const {
            int sum{};
            for (int i{}; i < hashGroups; i++) {
                sum += table[i].size();
            }

            if (!sum) {
                return true;
            }
            return false;
        }

        size_t getItemsCount() const {
            return itemsCount;
        }

        int hashFunction(size_t key) const {
            return key % hashGroups;
        }

        void insertItem(int key, ValueType value) {
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = cell.begin();
            bool keyExists = false;
            for (; bItr != cell.end(); bItr++) {
                if (bItr->first == key) {
                    keyExists = true;
                    bItr->second = value;
                    ++itemsCount;
                    cout << "WARNING: Key exists. Value replaced.\n";
                    break;
                }
            }

            if (!keyExists) {
                cell.emplace_back(key, value);
                ++itemsCount;
            }

            return;
        }

        void removeItem(size_t key) {
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = cell.begin();
            bool keyExists = false;
            for (; bItr != cell.end(); bItr++) {
                if (bItr->first == key) {
                    keyExists = true;
                    bItr = cell.erase(bItr); // Сдвигает итератор вперед
                    --itemsCount;
                    cout << "INFO: Item removed.\n";
                    break;
                }
            }

            if (!keyExists) {
                cout << "WARNING: Key not found. Pair not removed.\n";
            }

            return;
        }

        ValueType searchTable(size_t key) const {
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = cell.begin();
            bool keyExists = false;
            ValueType value;

            for (; bItr != cell.end(); bItr++) {
                if (bItr->first == key) {
                    keyExists = true;
                    value = bItr->second;
                }
            }

            if (!keyExists) {
                throw "[KeyError]: Key does not exists!";
            }
            else {
                return value;
            } 
        }

        void printTable() const {
            for (int i{}; i < hashGroups; ++i) {
                    if (table[i].size() == 0) continue;

                auto bItr = table[i].begin();
                for (; bItr != table[i].end(); bItr++) {
                    cout << "Key: " << bItr->first << " ---> Value: " << bItr->second << "\n";
                }
            }
            return;
        }


        class Iterator {
        private:
            const HashTable *table;
            size_t groupIndex;
            typename list<pair<size_t, ValueType>>::const_iterator listIter;
        
        public:
            Iterator(const HashTable *table, bool isBegin) : table(table) {
                if (isBegin) {
                    groupIndex = 0;
                    
                    // В поисках первой непустой группы
                    while (groupIndex < table->hashGroups && table->table[groupIndex].empty()) {
                        groupIndex++;
                    }
                    
                    if (groupIndex < table->hashGroups) {
                        listIter = table->table[groupIndex].begin();
                    }
                    else {
                        listIter = table->table[groupIndex].end();
                    }
                }
                else {
                    groupIndex = table->hashGroups;
                    listIter = table->table[table->hashGroups - 1].end(); // конец таблицы
                }
            }

            const pair<size_t, ValueType>& operator*() const { return *listIter; }

            Iterator &operator++() {
                if (groupIndex >= table->hashGroups) {
                    return *this; // Достигли конца таблицы
                }

                ++listIter;

            
                if (listIter == table->table[groupIndex].end()) { // Достигли конца текущего списка
                    ++groupIndex;
                    while (groupIndex < table->hashGroups && table->table[groupIndex].empty()) {
                        ++groupIndex; // Пропуск пусчтых таблиц
                    }

                    if (groupIndex < table->hashGroups) {
                        listIter = table->table[groupIndex].begin();
                    }
                }
                return *this;

            }

            bool operator!=(const Iterator &other) const {
                return groupIndex != other.groupIndex || listIter != other.listIter;
            }
        };


        Iterator begin() const {
            return Iterator(this, true);
        }

        Iterator end() const {
            return Iterator(this, false);
        }

};

#endif