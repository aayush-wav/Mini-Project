#pragma once
#include <string>

struct FeeRecord {
    int studentId;
    std::string studentName;
    float amount;
    FeeRecord* next;

    FeeRecord(int id, std::string name, float amt);
};

class FeeQueue {
public:
    FeeRecord* front;
    FeeRecord* rear;
    int size;

    FeeQueue();
    void enqueue(int id, std::string name, float amount);
    FeeRecord* dequeue();
    FeeRecord* peek();
    bool isEmpty();
    void display();
};
