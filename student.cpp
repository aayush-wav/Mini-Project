#include "student.h"
#include <iostream>
#include <iomanip>

Student::Student(int i, std::string n, int a, std::string g)
    : id(i), name(n), age(a), grade(g), next(nullptr) {}

StudentList::StudentList() : head(nullptr), count(0) {}

void StudentList::insert(Student* s) {
    s->next = head;
    head = s;
    count++;
}

void StudentList::remove(int id) {
    Student* cur = head;
    Student* prev = nullptr;
    while (cur) {
        if (cur->id == id) {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            cur->next = nullptr;
            count--;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

Student* StudentList::find(int id) {
    Student* cur = head;
    while (cur) {
        if (cur->id == id)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

void StudentList::display() {
    if (!head) {
        std::cout << "No students enrolled.\n";
        return;
    }
    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(20) << "Name"
              << std::setw(5) << "Age"
              << std::setw(8) << "Grade" << "\n";
    std::cout << std::string(39, '-') << "\n";
    Student* cur = head;
    while (cur) {
        std::cout << std::setw(6) << cur->id
                  << std::setw(20) << cur->name
                  << std::setw(5) << cur->age
                  << std::setw(8) << cur->grade << "\n";
        cur = cur->next;
    }
}
