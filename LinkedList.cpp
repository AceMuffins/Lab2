#include "LinkedList.h"
#include <iostream>
#include <cstdlib>

using namespace std;


void Data::generateRandomData() {
    profName = rand() % 26 + 65;
    num = rand() % 6 + 1;
    studentCount = rand()%30 + 1;
}


void LinkedList::print(){
    HashNode* current = head;
    while(current != nullptr){
        cout<<current->data.profName<<" "<<current->data.num<<" "<<current->data.studentCount<<endl;
        current = current->next;
    }
}

void LinkedList::push_front(long long key, Data newData){
    HashNode* newNode = new HashNode();
    newNode->key = key;
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
    if(tail == nullptr){
        tail = head;
    }
}

void LinkedList::push_back(long long key, Data newData){
    HashNode* newNode = new HashNode();
    newNode->key = key;
    newNode->data = newData;
    newNode->next = nullptr;
    if(head == nullptr){
        tail = newNode;
        head = tail;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

int LinkedList::size(){
    HashNode* current = head;
    int siz = 0;
    while(current != nullptr){
        siz++;
        current = current->next;
    }
    return siz;
}

Data LinkedList::get(int toGet){
    if(toGet < 0){
        cout<<"ERR: Invalid Index";
        return {};
    } else {
        HashNode* current = head;
        int index = 0;
        while(current != nullptr){
            if(index == toGet){
                return current->data;
            }
            index++;
            current = current->next;
        }
        cout<<"ERR: No Such Index";
        return {};
    }
}

Data LinkedList::pop_front(){
    if(head == nullptr){
        return {};
    } else if(head == tail){
        HashNode* temp = head;
        head = nullptr;
        tail = nullptr;
        return temp->data;
    } else {
        HashNode* temp = head;
        head = head->next;
        return temp->data;
    }
}

Data LinkedList::pop_back(){
    if(tail == nullptr){
        return {};
    } else if(head == tail){
        HashNode* temp = tail;
        head = nullptr;
        tail = nullptr;
        return temp->data;
    } else {
        HashNode* current = head;
        while(current->next != tail){
            current = current->next;
        }
        tail = current;
        current = tail->next;
        tail->next = nullptr;
        return current->data;
    }
}

void LinkedList::clear(){
    HashNode* current = head;
    HashNode* temp;
    while(current != nullptr){
        temp = current->next;
        delete current;
        current = temp;
    }
    delete current;
    delete temp;
    head = nullptr;
    tail = nullptr;
}
/*
void LinkedList::insert(Data* newData, int index){
    if(index == 0){
        push_front(newData);
    } else if (index < 0){
        cout<<"ERR: Invalid Index"<<endl;
    } else {
        HashNode* current = head;
        int ind = 0, flag = 0;
        while(current != nullptr){
            if(ind+1 == index){
                HashNode* newNode = new HashNode();
                newNode->data = *newData;
                newNode->next = current->next;
                current->next = newNode;
                flag = 1;
                break;
            }
            ind++;
            current = current->next;
        }
        if(current == nullptr && ind==index){
            push_back(newData);
        } else if (ind < index && flag == 0){
            cout<<"ERR: Invalid Index"<<endl;
        }
    }
}


void LinkedList::remov(long long key){
    HashNode* current = head;
    while(current != nullptr){
        if(current->next->key == key){
            current->next = current->next->next;
            delete current;
            break;
        }
        current = current->next;
    }
}*/