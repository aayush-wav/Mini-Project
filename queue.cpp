#include "queue.h"
#include <iostream>
#include <iomanip>

FeeRecord::FeeRecord(int id, std::string name, float amt)
    : studentId(id), studentName(name), amount(amt), next(nullptr) {}

FeeQueue::FeeQueue() : front(nullptr), rear(nullptr), size(0) {}

void FeeQueue::enqueue(int id, std::string name, float amount) {
    FeeRecord* rec = new FeeRecord(id, name, amount);
    if (!rear) {
        front = rear = rec;
    } else {
        rear->next = rec;
        rear = rec;
    }
    size++;
}

FeeRecord* FeeQueue::dequeue() {
    if (!front)
        return nullptr;
    FeeRecord* tmp = front;
    front = front->next;
    if (!front)
        rear = nullptr;
    tmp->next = nullptr;
    size--;
    return tmp;
}

FeeRecord* FeeQueue::peek() {
    return front;
}

bool FeeQueue::isEmpty() {
    return front == nullptr;
}

void FeeQueue::display() {
    if (!front) {
        std::cout << "Fee queue is empty.\n";
        return;
    }
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(20) << "Name"
              << std::setw(10) << "Amount" << "\n";
    std::cout << std::string(38, '-') << "\n";
    FeeRecord* cur = front;
    while (cur) {
        std::cout << std::setw(8) << cur->studentId
                  << std::setw(20) << cur->studentName
                  << std::setw(10) << cur->amount << "\n";
        cur = cur->next;
    }
}
