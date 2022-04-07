//
// Created by Ace Muffins on 07/04/2022.
//

#ifndef ASD_LAB2_LINKEDLIST_H
#define ASD_LAB2_LINKEDLIST_H

struct Data{
    char profName;
    int num;
    int studentCount;

    void generateRandomData();
};

struct HashNode{
    long long key;
    Data data;
    HashNode* next;
};

struct LinkedList{
    HashNode* head;
    HashNode* tail;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void print();
    void push_front(long long key, Data newData);
    void push_back(long long key, Data newData);
    int size();
    Data get(int toGet);
    Data pop_front();
    Data pop_back();
    void clear();
    //void insert(Data* newData, int index);
    void remov(long long key);

    ~LinkedList(){
        HashNode* current = head;
        if(current != nullptr){
            HashNode* temp;
            while(current != nullptr){
                temp = current->next;
                delete current;
                current = temp;
            }
            delete current;
            delete temp;
        }
    }
};

#endif //ASD_LAB2_LINKEDLIST_H
