#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

class HashTable
{  
    private:
        static const int hashGroups = 10;
        list<pair<int, string>> table [hashGroups];
    
    public:
        bool isEmpty() const;
        int hashFunction(int key);
        void insertItem(int key, string value);
        void removeItem(int key);
        string searchTable(int key) const;
        void printTable() const;
};

bool HashTable::isEmpty() const {
    int sum{};
    for (int i{}; i < hashGroups; i++) {
        sum += table[i].size();
    }

    if (!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) {
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            cout << "WARNING: Key exists. Value replaced.\n";
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key, value);
    }

    return;
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr); // Сдвигает итератор вперед
            cout << "INFO: Item removed.\n";
            break;
        }
    }

    if (!keyExists) {
        cout << "WARNING: Key not found. Pair not removed.\n";
    }

    return;
}

string HashTable::searchTable(int key) const {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            return bItr->second;
        }
    }

    if (!keyExists) {
        return ""
    }
}

void HashTable::printTable() const {
    for (int i{}; i < hashGroups; ++i) {
            if (table[i].size() == 0) continue;

        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++) {
            cout << "Key: " << bItr->first << " ---> Value: " << bItr->second << "\n";
        }
    }
    return;
}



#endif