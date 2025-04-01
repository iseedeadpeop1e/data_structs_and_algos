#include "hashtable.h"
#include <iostream>

using namespace std;


int main() {
    HashTable hashTable;

    if (hashTable.isEmpty()) {
        cout << "CORRECT.\n";
    }
    else {
        cout << "ERROR.\n";
    }

    hashTable.insertItem(412, "Roman");
    hashTable.insertItem(415, "Ivan");
    hashTable.insertItem(4121, "Anton");
    hashTable.insertItem(417, "Gena");
    hashTable.insertItem(4126, "Stas");
    hashTable.insertItem(41233, "Den");
    hashTable.insertItem(4, "Richard");

    hashTable.printTable();
    hashTable.removeItem(412);
    hashTable.removeItem(100);

    if (hashTable.isEmpty()) {
        cout << "ERROR.\n";
    }
    else {
        cout << "CORRECT.\n";
    }
}