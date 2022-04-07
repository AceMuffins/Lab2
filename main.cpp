#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "LinkedList.h"

#include <unordered_map>

using namespace std;

long long generateRandLong(){
    //12-16
    long long num = 0;
    int size = rand() % 5 + 11;
    for(int i = 0; i < size; i++){
        num += (rand()%10) * pow(10, i);
    }
    return num;
}
struct HashTable{
    LinkedList* bucketsArray;
    double loadFactor = 0;
    double maxLoadFactor = 0.5;
    int bucketSize = 10000;

    HashTable(){
        bucketsArray = new LinkedList[bucketSize];
    }

    long long hash(long long key){
        long long prime = 768614336404564651;
        long long hash;
        int a = 45;
        int b = 2763;
        hash = ((a * key + b) % prime) % bucketSize;
        return hash;
    }

    Data* find(long long key){
        long long index = hash(key);
        LinkedList* list = &bucketsArray[index];
        HashNode* current = list->head;
        while(current != nullptr){
            if(current->key == key){
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void insert(long long key, Data value){

        double newLoadFactor = (size()+1.0)/bucketSize;
        if(newLoadFactor > maxLoadFactor){
            relocateMemory();
            newLoadFactor = (size()+1.0)/bucketSize;
        }
        loadFactor = newLoadFactor;

        long long index = hash(key);
        LinkedList* list = &bucketsArray[index];
        if(find(key) != nullptr){
            *find(key) = value;
        } else {
            list->push_front(key, value);
        }

    }

    void erase(long long key){
        long long index = hash(key);
        LinkedList* list = &bucketsArray[index];
        HashNode* current = list->head;
        HashNode* previous = nullptr;
        while(current != nullptr){
            if(current->key == key){
                if(previous == nullptr){
                    list->head = current->next;
                    delete current;
                } else if(current->next == nullptr){
                    list->tail = previous;
                    delete current;
                } else {
                    previous = current->next;
                    delete current;
                }
                break;
            }
            previous = current;
            current = current->next;
        }
        /*
        if(find(key) != nullptr){
            HashNode* current = list->head;
            if(current->next == nullptr){
                list->head = nullptr;
                delete current;
            } else {
                while(current != nullptr){
                    if(current->next->key == key){
                        current->next = current->next->next;
                        delete current;
                        break;
                    }
                    current = current->next;
                }
            }
        }
        */
    }

    long long size(){ //fix me
        long long siz = 0;
        for(int i = 0; i < bucketSize; i++){
            siz += bucketsArray[i].size();
        }
        return siz;
    }

    void relocateMemory(){
        bucketSize *= 2;
        LinkedList* temp = new LinkedList[bucketSize];
        for(int i = 0; i < (bucketSize/2); i++){
            if(bucketsArray[i].size()!=0){
                LinkedList* list = &bucketsArray[i];
                HashNode* current = list->head;
                while(current != nullptr){
                    temp[i].push_front(current->key, current->data);
                    current = current->next;
                }
            }
        }
        delete[] bucketsArray;
        bucketsArray = temp;
    }

    void print(long long key){
        if(find(key) != nullptr){
            cout<<find(key)->studentCount<<endl;
        } else {
            cout<<"No such element."<<endl;
        }
    }
};

Data genRandData(){
    char profName = rand() % 26 + 65;
    int num = rand() % 6 + 1;
    int studentCount = rand()%30 + 1;
    return {profName, num, studentCount};
}

bool testHashTable()
{
    const int iters = 500;
    const int keysAmount = iters * 1;
// generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters];
    long long* keysToErase = new long long[iters];
    long long* keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
// test my HashTable:
    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], genRandData());
    }

    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
// test STL hash table:
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({keysToInsert[i], Data()});
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
         ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
         << ", found amount: " << stlFoundAmount << endl << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
                                                                        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main() {
    srand(time(nullptr));
    testHashTable();

    return 0;
}
